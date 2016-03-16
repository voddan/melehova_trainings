//
// Created by voddan on 15/03/16.
//

#include <stdio.h>
#include "loglib.h"

void somefunc() {
    log_write(LOG_WARN, "hello should not do that!!");
    log_write(LOG_ERROR, "that's a trap!");

}

int main(int argn, char ** args) {
    printf("hello world\n");

//    log_init(stderr, 256, LOG_DEBUG);
//    flogger("log", LOG_DEBUG);
    logger(LOG_DEBUG);

    log_write(LOG_DEBUG, "hello world!");

    log_flush();

    log_write(LOG_INFO, "paparem!");


    somefunc();

    log_write(LOG_DEBUG, "yups");


    log_set_level(LOG_WARN);

    log_write(LOG_DEBUG, "you can't see me!");

    log_write(LOG_WARN, "I am after some LOG_DEBUG");

//    log_flush();

    return 0;
}

