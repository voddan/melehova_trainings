//
// Created by voddan on 15/03/16.
//

#include <stdio.h>
#include "loglib.h"

void somefunc() {
    log_write(WARN, "hello should not do that!!");
    log_write(ERROR, "that's a trap!");

}

int main(int argn, char ** args) {
    printf("hello world\n");


    log_init(stderr, 25, DEBUG);


    log_write(DEBUG, "hello world!");

//    log_flush();

    log_write(INFO, "paparem!");


    somefunc();

    log_set_level(WARN);

    log_write(DEBUG, "you can't see me!");

    return 0;
}

