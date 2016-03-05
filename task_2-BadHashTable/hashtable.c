//
// Created by voddan on 25/02/16.
//

#include <stdio.h>
#include "HASH/hashfunction.h"
#include "HASH/hashfunction_bfm.h"

int main(int argn, char ** args) {

    printf("gonna test some hash functions!\n");

    int key1 = 239;
    int hash1 = hash_function_vodopian(key1);
    printf("hash_function_vodopian: %d -> %d\n", key1, hash1);

    int key2 = key1;
    int hash2 = hash_function_vodopian_bfm(key2);
    printf("hash_function_vodopian: %d -> %d\n", key2, hash2);

    return 0;
}

struct HT {

};

