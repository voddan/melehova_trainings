//
// Created by voddan on 10/03/16.
//

#include <stdio.h>

#define ROUNDS (1000)

int main(int argn, char ** args) {
    printf("start\n");

    FILE * input = fopen("/dev/random", "ro");

    for (int i = 0; i < ROUNDS; ++i) {
        getc(input);
    }

    printf("stop\n");

    return 0;
}