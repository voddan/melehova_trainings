//
// Created by voddan on 10/03/16.
//

#include <stdio.h>

int main(int argn, char ** args) {
    printf("start\n");

    FILE * input = fopen("/dev/random", "ro");

    getc(input);
    getc(input);
    getc(input);
    getc(input);
    getc(input);


    printf("stop\n");

    return 0;
}