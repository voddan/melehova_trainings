//
// Created by voddan on 28/02/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "hashfunction_bfm.h"

int main(int argn, char ** args) {
    printf("testing hash_function_vodopian_bfm\n");

    int key1 = 239;
    int hash1 = hash_function_vodopian_bfm(key1);
    printf("hash_function_vodopian: %d -> %d\n", key1, hash1);


    return 0;
}