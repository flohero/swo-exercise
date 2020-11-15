#ifndef SWO3_ROMAN_H
#define SWO3_ROMAN_H

static const int ROMAN_MAPPING_COUNT = 12;

int roman_to_decimal(char const r[]);

void decimal_to_roman(int d, char r[]);

#endif //SWO3_ROMAN_H
