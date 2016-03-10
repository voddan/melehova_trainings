//
// Created by voddan on 10/03/16.
//

#include <stdio.h>


int main(int argn, char ** args) {
    if (argn < 2) {
        printf("USAGE: test_n N\n");
        return 1;
    }

    printf("start\n");

    FILE * input = fopen("/dev/random", "ro");

    long N = atol(args[1]);

    for (int i = 0; i < N; ++i) {
        getc(input);
    }

    printf("stop\n");

    return 0;
}