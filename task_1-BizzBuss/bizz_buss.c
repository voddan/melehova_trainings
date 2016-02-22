//
// Created by Daniil Vodopian (376 MIPT) on 21/02/16.
// Compile C99
//

#include <stdio.h>
#include <tic.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_LENGTH (100)

enum ERROR_CODES {
    ERR_FILE_NOT_FOUND = 0,
    ERR_NUM_TOO_BIG = 1
};

void bizz_buss(FILE *);
void print_usage();

int main(int argn, char ** args) {
    if (argn > 1 && 0 == strcmp(args[1], "--help")) {
        print_usage();
        return 0;
    }

    FILE * input = (argn > 1) ? fopen(args[1], "ro") : stdin;

    if (!input) {
        fprintf(stderr, "ERROR: file not found: %s", args[1]);
        exit(ERR_FILE_NOT_FOUND);
    }

    bizz_buss(input);

    fclose(input);
    return 0;
}

void print_usage() {
    printf("    *** BIZZ-BUSS ***\n"
           "USAGE: bizz_buss [--help] [path to a text file]\n"
           "\n"
           "| Reads the input from `stdin` or a file if provided;\n"
           "| Prints it, with replacements:\n"
           "|     * numbers divisible by  3 are replaced by \"bizz\",\n"
           "|     * numbers divisible by 15 are replaced by \"bissbuzz;\"\n"
           "|     * numbers divisible by  5 are replaced by \"buss\",\n"
           "| Ignores the minus sign;\n"
           "| A number may not be surrounded by anything but `\\t`, ` `, `\\n`;\n"
           "| The numbers must be shorter then %d digits each.\n"
           "\n"
           "Created by Daniil Vodopian (voddan) on 21/02/16\n", MAX_NUMBER_LENGTH);
}


bool is_mod_5(int);
bool is_mod_3(int);

bool is_digit(int);
bool is_space(int);

void print_char_arr(char *, int);

void bizz_buss(FILE * file) {
    char num[MAX_NUMBER_LENGTH] = {};


    bool was_number = false;
    bool was_space = true;

    int digit_sum = 0;
    int digit_last = -1;
    int digit_count = 0;


    int ch;
    while (EOF != (ch = getc(file))) {

        if (is_digit(ch) && (was_space || was_number)) {

            int digit = ch - '0';

            was_number = true;
            digit_sum += digit;
            digit_last = digit;

            if (digit_count >= MAX_NUMBER_LENGTH) {
                fprintf(stderr, "ERROR: a number has more than %d digits", MAX_NUMBER_LENGTH);
                exit(ERR_NUM_TOO_BIG);
            }
            num[digit_count] = (char) ch;
            digit_count += 1;

        } else if (was_number) {
            if (is_space(ch)) {
                bool mod_3 = is_mod_3(digit_sum);
                bool mod_5 = is_mod_5(digit_last);

                if (mod_3 && mod_5) {
                    printf("bizzbuzz");
                } else if (mod_3) {
                    printf("bizz");
                } else if (mod_5) {
                    printf("buss");
                } else {
                    print_char_arr(num, digit_count);
                }

            } else {
                print_char_arr(num, digit_count);
            }

            was_number = false;
            digit_sum = 0;
            digit_last = -1;
            digit_count = 0;

            printf("%c", ch);

        } else {
            printf("%c", ch);
        }

        was_space = is_space(ch);
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

bool is_digit(int ch) {
    return '0' <= ch && ch <= '9';
}

bool is_space(int ch) {
    return ' ' == ch || '\n' == ch || '\t' == ch || EOF == ch;
}

void print_char_arr(char * arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%c", arr[i]);
    }
}
