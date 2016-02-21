//
// Created by voddan on 21/02/16.
// uses C99
//

#include <stdio.h>
#include <tic.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_NUMBER_LENGTH (100)

void bizz_buss(FILE *);

int main(int argn, char ** args) {
    printf("    *** BIZZ-BUSS ***\n"
           "USAGE: bizz_buss [path to a text file]\n"
           "\n"
           "| Reads the input from `stdin` or a file if provided;\n"
           "| Prints it, with replacements:\n"
           "|     * numbers divisible by  3 are replaced by \"bizz\",\n"
           "|     * numbers divisible by 15 are replaced by \"bissbuzz;\"\n"
           "|     * numbers divisible by  5 are replaced by \"buss\",\n"
           "| Ignores the minus sign;\n"
           "| The numbers must be shorter then %d digits each.\n"
           "\n"
           "Created by Daniil Vodopian (voddan) on 21/02/16\n"
           "-----------------------------------------------\n", MAX_NUMBER_LENGTH);


    FILE * input = (argn > 1) ? fopen(args[1], "ro") : stdin;

    if (!input) {
        fprintf(stderr, "ERROR: file not found: %s", args[1]);
        exit(1);
    }


    bizz_buss(input);

    fclose(input);
    return 0;
}


bool is_mod_5(int);
bool is_mod_3(int);

void bizz_buss(FILE * file) {
    char num[MAX_NUMBER_LENGTH] = {};

    bool is_number = false;

    int digit_sum = 0;
    int digit_last = -1;
    int digit_count = 0;


    int ch;
    while (EOF != (ch = getc(file))) {

        if ('0' <= ch && ch <= '9') {
            int digit = ch - '0';

            is_number = true;
            digit_sum += digit;
            digit_last = digit;

            if (digit_count >= MAX_NUMBER_LENGTH) {
                fprintf(stderr, "ERROR: a number has more than %d digits", MAX_NUMBER_LENGTH);
                exit(2);
            }
            num[digit_count] = (char) ch;
            digit_count += 1;
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
                for (int i = 0; i < digit_count; i++)
                    printf("%c", num[i]);
            }

            is_number = false;
            digit_sum = 0;
            digit_last = -1;
            digit_count = 0;

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
    int power3[] = {729, 243, 81, 27, 9, 3};  // if MAX_NUMBER_LENGTH ~ 100, then sum < 900

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
