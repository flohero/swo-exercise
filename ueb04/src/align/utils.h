#ifndef SWO3_UTILS_H
#define SWO3_UTILS_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_SIZE 100

/**
 * An enum to differentiate between the different matrix types
 */
typedef enum matrix_t {
  levenshtein_mat = 0, shared_substr_mat = 1, fuzzy_search_mat = 2
} matrix_t;

/**
 * The different operations in a levenshtein, longest substring and fuzzy search matrix
 */
typedef enum operations {
  insert = 'I', delete = 'D', change = 'C', noop = ' '
} operations;

typedef struct levenshtein_rec {
  bool left;
  bool up;
  bool diag;
  size_t val;
} levenshtein_rec;

typedef levenshtein_rec matrix[MAX_SIZE][MAX_SIZE];

size_t min_of_3(size_t a, size_t b, size_t c);

size_t max_of_3(size_t a, size_t b, size_t c);

void strcat_char(char *str, char c);

size_t revstr(char str[]);

void build_str_matrix(char *str1, char *str2, matrix m, matrix_t mat_type);

void print_str_matrix(char *str1, char *str2, matrix m);

void print_edit_sequences(char *str1, char *str2, matrix_t mat_type);

#endif //SWO3_UTILS_H
