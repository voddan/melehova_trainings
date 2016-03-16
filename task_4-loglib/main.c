//
// Created by voddan on 15/03/16.
//

#include <stdio.h>
#include "loglib.h"

void somefunc() {
    warning("hello should not do that!!");
    error("that's a trap!");

}

int main(int argn, char ** args) {
    printf("hello world\n");

//    log_init(stderr, 256, LOG_DEBUG);
//    flogger("log", LOG_DEBUG);
//    logger(LOG_DEBUG);
    logERR(LOG_DEBUG);

    debug("hello world!");

    log_flush();

    info("pam-param!");


    somefunc();

    debug("yups");


    log_set_level(LOG_WARN);

    debug("you can't see me!");

    warning("I am after some LOG_DEBUG");

//    log_flush();

    return 0;
}

