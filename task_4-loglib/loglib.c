//
// Created by voddan on 15/03/16.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <execinfo.h>
#include <time.h>
#include "loglib.h"

typedef struct {
    char * buf;
    size_t buf_size;
    char * eob;
    LogLevel level;
    FILE * stream;
} Logger;


/** input `Logger` on start,
 * input `NULL` to clear,
 * any other input has no effect
 *
 * returns NULL if not initialised
 * */
Logger * _Logger_singleton_set(bool set_logger_instance, Logger * logger_instance) {
    static Logger * instance = NULL;

// todo: multi-thread!
    if (set_logger_instance) {
        instance = logger_instance;
    }

    return instance;
}

Logger * Logger_singleton() {
    return _Logger_singleton_set(false, NULL);
}

Logger * Logger_new(size_t size, LogLevel level, FILE * stream) {
    Logger * log = (Logger *) malloc(sizeof(Logger));

    log->buf_size = size;
    log->buf = (char *) calloc(sizeof(char), log->buf_size);
    log->eob = log->buf;
    log->level = level;
    log->stream = stream;

    _Logger_singleton_set(true, log);

    return log;
}

void Logger_destruct() {
    Logger * instance = Logger_singleton();

    log_flush();

    free(instance->buf);
    free(instance);

    _Logger_singleton_set(true, NULL);
}

//---- PUBLIC API -----------------

void log_init(FILE * stream, size_t size, LogLevel level) {
    if (Logger_singleton()) {
        fprintf(stderr, "FATAL> logger already exists\n");
        log_write(_print_log_level, "FATAL:: logger already exists\n");
        exit(EXIT_FAILURE);
    }

    Logger_new(size, level, stream);
    atexit(Logger_destruct);

    time_t tm = time(NULL);
    log_write(_print_log_level, ctime(&tm));
}

/** fast function, no memory allocations */
void log_write(LogLevel level, char const * msg) {
    Logger * log = Logger_singleton();
    if (!log) {
        fprintf(stderr, "FATAL> init logger before writing\n");
        exit(EXIT_FAILURE);
    }

    if (log->level > level)  // filtering by the log level
        return;

    if (log->eob > log->buf + log->buf_size / 2)
        log_flush();


    char * prefix;
    switch (level) {
        case DEBUG:
            prefix = "DEBUG";
            break;
        case INFO:
            prefix = "INFO ";
            break;
        case WARN:
            prefix = "WARN ";
            break;
        case ERROR:
            prefix = "ERROR";
            break;
        default:
            prefix = "";
    }

    time_t tm = time(NULL);
    char timestamp[30] = {};
    strftime(timestamp, sizeof(timestamp), "%T", localtime(&tm));

    size_t size_left = log->buf + log->buf_size - log->eob - 1;

    // todo: it is not thread safe to write first and increment log->eob second
    if (_print_log_level == level) {
        log->eob += snprintf(log->eob, size_left, "%s", msg);
    } else {
        log->eob += snprintf(log->eob, size_left, "%s [%s] :: %s\n", prefix, timestamp, msg);
    }

    if (ERROR == level) {
        log_flush();

        void * callstack[CALLSTACK_MAX_SIZE];
        int callstack_len = backtrace(callstack, CALLSTACK_MAX_SIZE);

        // todo: multi-thread!
        backtrace_symbols_fd(callstack + 1, callstack_len - 2, fileno(log->stream));
    }

    //  todo: multithread!
    if (log->eob > log->buf + log->buf_size)
        log->eob += sprintf(log->eob, "\n");
}

void log_flush() {
    Logger * log = Logger_singleton();
    if (!log) {
        fprintf(stderr, "FATAL> init logger before writing\n");
        exit(EXIT_FAILURE);
    }

    fwrite(log->buf, log->eob - log->buf, 1, log->stream);
    fflush(log->stream);

    log->eob = log->buf;
}

void log_set_level(LogLevel level) {
    Logger * log = Logger_singleton();
    if (!log) {
        fprintf(stderr, "FATAL> init logger before writing\n");
        exit(EXIT_FAILURE);
    }

    // todo: log the new logger level (??)
    log->level = level;
}
