//
// Created by voddan on 25/02/16.
//

#include "hashfunction.h"

int32_t hash_function_vodopian(int32_t key) {
    key = (key << 15) - key - 1;
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = (key + (key << 3)) + (key << 11);
    key = key ^ (key >> 16);
    return key;
}

// https://gist.github.com/badboy/6267743#32-bit-mix-functions
