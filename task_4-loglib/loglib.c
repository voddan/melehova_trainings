//
// Created by voddan on 15/03/16.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "loglib.h"

typedef struct {
    char * buf;
    size_t buf_size;
} Logger;


void Logger_destruct();

Logger * Logger_new(size_t size) {
    Logger * log = (Logger *) malloc(sizeof(Logger));
    log->buf_size = size;
    log->buf = (char *) calloc(sizeof(char), log->buf_size);

    atexit(Logger_destruct);

    return log;
}

Logger * Logger_singleton_set(Logger * log);
Logger * Logger_singleton();

void Logger_destruct() {
    Logger * instance = Logger_singleton();

    free(instance->buf);
    free(instance);

    Logger_singleton_set(NULL);
}

/** input `Logger` on start, input `NULL` to clear, any other input has no effect */
Logger * Logger_singleton_set(Logger * log) {
    static Logger * instance = NULL;

    if (!instance || !log) {
        instance = log;
    }

    return instance;
}

Logger * Logger_singleton() {
    return Logger_singleton_set((Logger *) true);
}

//---- PUBLIC API -----------------

void log_init() {
    Logger * log = Logger_new(256);
    Logger_singleton_set(log);
}

void log_write(LogLevel level, char const * msg) {

}

void log_flush() {

}

void log_set_level(LogLevel level) {

}
