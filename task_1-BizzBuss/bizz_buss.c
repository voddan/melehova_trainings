//
// Created by voddan on 21/02/16.
// uses C99
//

#include <stdio.h>
#include <tic.h>
#include <assert.h>

void bizz_buss(FILE *);


int main(int argn, char ** args) {
    printf("    *** BIZZ-BUSS ***\n"
                   "USAGE: Takes 0 or 1 argument: path to a text file\n"
                   "\n"
                   "Reads the input from `stdin` or a file if provided;\n"
                   "prints it, with replacements:\n"
                   "    * numbers divisible by  3 are replaced by \"bizz\",\n"
                   "    * numbers divisible by  5 are replaced by \"buss\",\n"
                   "    * numbers divisible by 15 are replaced by \"bissbuzz;\"\n"
                   "ignores the minus sign\n"
                   "\n"
                   "Created by Daniil Vodopian (voddan) on 21/02/16\n"
                   "-----------------------------------------------\n");


    FILE * input = (argn > 1) ? fopen(args[1], "ro") : stdin;

    if (!input) {
        printf("ERROR: file not found: %s", args[1]);
        return 1;
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
