//
// Created by voddan on 21/02/16.
// uses C99
//

#include <stdio.h>
#include <stdlib.h>
#include <tic.h>
#include <assert.h>

void bizz_buss(FILE *);

int main(int argn, char ** args) {
    char filename[] = "/Users/voddan/Programming/melehova_trainings/task_1-BizzBuss/input.txt";

    FILE * input = fopen(filename, "ro");
    if (!input) {
        printf("ERROR: file not found: %s", filename);
        exit(1);
    }


    bizz_buss(input);

    fclose(input);
    return 0;
}

//char by char
//input source

bool is_mod_5(int);

bool is_mod_3(int);

void bizz_buss(FILE * file) {
    bool is_number = false;

    int digit_sum = 0;
    int digit_last = -1;
    int num = 0;  //todo


    int ch;
    while (EOF != (ch = getc(file))) {

        if ('0' <= ch && ch <= '9') {
            int digit = ch - '0';

            is_number = true;
            digit_sum += digit;
            digit_last = digit;
            num = 10 * num + digit;
        } else if (is_number) {
            bool mod_3 = is_mod_3(digit_sum);
            bool mod_5 = is_mod_5(digit_last);


            if (mod_3 && mod_5) {
                printf("bizzbuzz");
            } else if (mod_3) {
                printf("bizz");
            } else if (mod_5) {
                printf("buss");
            } else {
                printf("%d", num);
            }

            is_number = false;
            digit_sum = 0;
            digit_last = -1;
            num = 0;

            printf("%c", ch);
        } else {
            printf("%c", ch);
        }
    }
}

bool is_mod_5(int last) {
    return last == 0 || last == 5;
}

bool is_mod_3(int sum) {
    int power3[] = {729, 243, 81, 27, 9, 3};

    int m = sum;

    int i = 0;
    while (m > 2) {
        while (m >= power3[i]) {
            m -= power3[i];
        }
        i += 1;
    }

    assert(m == sum % 3);
    return m == 0;
}
