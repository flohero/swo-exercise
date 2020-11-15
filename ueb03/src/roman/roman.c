#include <memory.h>
#include <stdio.h>
#include "roman.h"

static int get_value_from_roman(char roman_digit);

struct Digit_Counter {
    char roman_digit;
    int count;
};

int roman_to_decimal(char const r[]) {
    int sum = 0;
    char curr_roman_digit = r[0];
    struct Digit_Counter digit_counter;
    digit_counter.roman_digit = curr_roman_digit;
    digit_counter.count = 0;

    for (int i = 0; r[i] != '\0'; curr_roman_digit = r[++i]) {
        int digit_val = get_value_from_roman(curr_roman_digit);
        // Not a roman digit
        if (digit_val == 0) {
            return -1;
        }
        if (digit_counter.roman_digit == curr_roman_digit) {
            digit_counter.count++;
        } else {
            digit_counter.roman_digit = curr_roman_digit;
            digit_counter.count = 1;
        }
        // Multiple if statements to be readable
        // Check all digits which are only allowed to occur once
        if (digit_counter.count > 1
            && (curr_roman_digit == 'V' || curr_roman_digit == 'L' || curr_roman_digit == 'D')) {
            return -1;
        }

        // Check all digits which are allowed to occur thrice
        if (digit_counter.count > 3
            && (curr_roman_digit == 'I' || curr_roman_digit == 'X' || curr_roman_digit == 'C')) {
            return -1;
        }
        // Check if there are multiple digits after each other, followed by a higher one
        if (digit_counter.count > 1 && digit_val < get_value_from_roman(r[i + 1])) {
            return -1;
        }
        // peak ahead and check if this digit is lower than the next one
        sum += digit_val < get_value_from_roman(r[i + 1])
               ? -digit_val : digit_val;
    }
    return sum;
}

static int get_value_from_roman(char const roman_digit) {
    switch (roman_digit) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
    }
}

/* Define private structs in the c file */
typedef struct {
    char *roman_num;
    int value;
} roman_mapping;

const roman_mapping mapping[13] = {{"I",  1},
                                   {"IV", 4},
                                   {"V",  5},
                                   {"IX", 9},
                                   {"X",  10},
                                   {"XL", 40},
                                   {"L",  50},
                                   {"XC", 90},
                                   {"C",  100},
                                   {"CD", 400},
                                   {"D",  500},
                                   {"CM", 900},
                                   {"M",  1000}};

void decimal_to_roman(int d, char r[]) {
    // Since in the roman numerals do not have the concept of zero
    if (d > 3000 || d < 1) {
        printf("Not a valid number, should be between 1 and 3000!\n");
        return;
    }
    for (int i = ROMAN_MAPPING_COUNT; i >= 0; i--) {
        int res = d / mapping[i].value;
        for (int j = 0; j < res; j++) {
            strcat(r, mapping[i].roman_num);
        }
        d -= res * mapping[i].value;
    }
}
