//
// Created by voddan on 28/02/16.
//

#include <stdio.h>
#include <stdlib.h>

#define DEBUG (false)

#include "hashfunction.h"
#include "hashfunction_bfm.h"


int main() {

    printf("testing hash functions on being identical\n");

    for (int i = 0; i < 20; i++) {
        int32_t key = (int32_t) random();
        int hash1 = hash_function_vodopian(key);
        int hash2 = hash_function_vodopian_bfm(key);

        if (hash1 == hash2)
            printf(" ok | %8x -> %8x\n", key, hash1);
        else
            printf("ERR | %8x -> %8x, %8x\n", key, hash1, hash2);


    }

    return 0;
}