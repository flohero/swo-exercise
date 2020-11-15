#include <stddef.h>
#include <memory.h>
#include "align.h"
#include "utils.h"

/**
 * How many steps are needed to transform str1 to str2 and vice versa.
 * @returns how many operations are needed to transform source to dest
 */
size_t levenshtein(char *str1, char *str2) {
  matrix m;
  build_str_matrix(str1, str2, m, levenshtein_mat);
  return m[strlen(str2)][strlen(str1)].val;
}

void print_levenshtein_edit_sequences(char *str1, char *str2) {
  print_edit_sequences(str1, str2, levenshtein_mat);
}


void print_longest_shared_substr(char *str1, char *str2) {
  print_edit_sequences(str1, str2, shared_substr_mat);
}

void print_fuzzy_search(char *str1, char *str2) {
  print_edit_sequences(str1, str2, fuzzy_search_mat);
}
