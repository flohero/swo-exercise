#include <stdlib.h>
#include <stdio.h>
#include "roman.h"
// The max length of a roman number under 3000 is 14.
// The longest number is 2888 or MMDCCCLXXXVIII
#define MAX_ROMAN_NUM_SIZE 14

void test_roman_to_decimal() {
    // Simple Inputs
    char *cxi = "CXI";
    printf("'%s' is %d; Expected: 111\n", cxi, roman_to_decimal(cxi));
    char *cxxiii = "CXXIII";
    printf("'%s' is %d; Expected: 123\n", cxxiii, roman_to_decimal(cxxiii));
    char *xc = "XC";
    printf("'%s' is %d; Expected: 90\n", xc, roman_to_decimal(xc));
    char *mcmlxv = "MCMLXV";
    printf("'%s' is %d; Expected: 1965\n", mcmlxv, roman_to_decimal(mcmlxv));
    char *mmdccclxxxviii = "MMDCCCLXXXVIII";
    printf("'%s' is %d; Expected: 2888\n", mmdccclxxxviii, roman_to_decimal(mmdccclxxxviii));

    // Edge Cases
    char *iiii = "IIII";
    printf("'%s' is %d; Expected: -1\n", iiii, roman_to_decimal(iiii));
    char *xxxx = "XXXX";
    printf("'%s' is %d; Expected: -1\n", xxxx, roman_to_decimal(xxxx));
    char *cccc = "CCCC";
    printf("'%s' is %d; Expected: -1\n", cccc, roman_to_decimal(cccc));
    char *vv = "VV";
    printf("'%s' is %d; Expected: -1\n", vv, roman_to_decimal(vv));
    char *ll = "LL";
    printf("'%s' is %d; Expected: -1\n", ll, roman_to_decimal(ll));
    char *dd = "DD";
    printf("'%s' is %d; Expected: -1\n", dd, roman_to_decimal(dd));
    char *mmm = "MMM";
    printf("'%s' is %d; Expected: -1\n", mmm, roman_to_decimal(mmm));

    char *empty = "";
    printf("'%s' is %d; Expected: 0\n", empty, roman_to_decimal(empty));
    char *wrong_char = " ";
    printf("'%s' is %d; Expected: -1\n", wrong_char, roman_to_decimal(wrong_char));
}

void test_decimal_to_roman() {
    // Simple Numbers
    char iii[MAX_ROMAN_NUM_SIZE] = { '\0' };
    int dec = 3;
    decimal_to_roman(dec, iii);
    printf("%d is '%s'; Expected: III\n", dec, iii);

    char cxi[MAX_ROMAN_NUM_SIZE] = { '\0' };
    dec = 111;
    decimal_to_roman(dec, cxi);
    printf("%d is '%s'; Expected: CXI\n", dec, cxi);

    char cxxiii[MAX_ROMAN_NUM_SIZE] = { '\0' };
    dec = 123;
    decimal_to_roman(dec, cxxiii);
    printf("%d is '%s'; Expected: CXXIII\n", dec, cxxiii);

    char xc[MAX_ROMAN_NUM_SIZE] = { '\0' };
    dec = 90;
    decimal_to_roman(dec, xc);
    printf("%d is '%s'; Expected: XC\n", dec, xc);

    char mcmlxv[MAX_ROMAN_NUM_SIZE] = { '\0' };
    dec = 1965;
    decimal_to_roman(dec, mcmlxv);
    printf("%d is '%s'; Expected: MCMLXV\n", dec, mcmlxv);

    char r[MAX_ROMAN_NUM_SIZE] = { '\0' };
    dec = 2888;
    decimal_to_roman(dec, r);
    printf("%d is '%s'; Expected: MMDCCCLXXXVIII\n", dec, r);

    // Edge Case
    // This array should not be used
    char empty[MAX_ROMAN_NUM_SIZE] = { '\0' };
    dec = 0;
    decimal_to_roman(dec, empty);
    printf("Expected: Error\n");

    dec = 3001;
    decimal_to_roman(dec, empty);
    printf("Expected: Error\n");
}

int main(void) {
    test_decimal_to_roman();
    return EXIT_SUCCESS;
}


