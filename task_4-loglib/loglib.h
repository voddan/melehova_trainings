//
// Created by voddan on 15/03/16.
//

#ifndef MELEHOVA_TRAININGS_LOGLIB_H
#define MELEHOVA_TRAININGS_LOGLIB_H

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    size
} LogLevel;

const LogLevel DEFAULT_LOG_LEVEL = INFO;

void log_init();

void log_write(LogLevel level, char const * msg);

void log_flush();

void log_set_level(LogLevel level);

#endif //MELEHOVA_TRAININGS_LOGLIB_H
