#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

/** Static Function Prototypes **/

static size_t get_minimum_index(levenshtein_rec array[], size_t len);

static void
print_str_except_on_operation(char *str, const char *levenshtein_seq,
                              operations op, size_t start);

static size_t
build_str_matrix_reverse_edit_sequences(char *str1, char *str2, size_t row,
                                        size_t col, size_t end_col, size_t *index,
                                        char paths[][100], matrix m);

static void init_longest_shared_substr_matrix(size_t num_of_cols, size_t num_of_rows,
                                              matrix m);

static void init_levenshtein_matrix(size_t num_of_cols, size_t num_of_rows,
                                    matrix m);

static void init_fuzzy_search_matrix(size_t num_of_cols, size_t num_of_rows,
                                     matrix m);


/**
 * @return The minimum of three numbers
 */
size_t min_of_3(const size_t a, const size_t b, const size_t c) {
  return a < b
         ? (a < c ? a : c)
         : (b < c ? b : c);
}

/**
 * @return The maximum of three numbers
 */
size_t max_of_3(const size_t a, const size_t b, const size_t c) {
  return a > b
         ? (a > c ? a : c)
         : (b > c ? b : c);
}

/**
 * Concat a char onto a string
 */
void strcat_char(char *str, char c) {
  char str_c[1] = {c};
  strcat(str, str_c);
}

/**
 * Reverses a string in place
 * @returns the length of the string
 */
size_t revstr(char str[]) {
  size_t length = strlen(str);
  for (size_t i = 0; i < length / 2; i++) {
    char tmp = str[length - i - 1];
    str[length - i - 1] = str[i];
    str[i] = tmp;
  }
  return length;
}

/**
 * Build a string matrix
 * @param mat_type which type of matrix should be generated.
 * There are three type: levenshtein matrix, longest substring matrix and fuzzy search matrix
 */
void build_str_matrix(char *str1, char *str2, matrix m,
                      matrix_t mat_type) {
  size_t len1 = strlen(str1), len2 = strlen(str2);

  // Use a compare function
  size_t (*comp_func)(size_t, size_t, size_t) = min_of_3;
  switch (mat_type) {
    case levenshtein_mat:
      init_levenshtein_matrix(len1, len2, m);
      break;
    case fuzzy_search_mat:
      init_fuzzy_search_matrix(len1, len2, m);
      break;
    case shared_substr_mat:
      init_longest_shared_substr_matrix(len1, len2, m);
      comp_func = max_of_3;
      break;
    default:
      return;
  }

  for (size_t i = 1; i <= len2; i++) {
    for (size_t j = 1; j <= len1; j++) {
      size_t up_val, left_val, diag_val;
      switch (mat_type) {
        // levenshtein and fuzzy search calculate the matrix the same way
        case levenshtein_mat:
        case fuzzy_search_mat:
          up_val = m[i - 1][j].val + 1;
          left_val = m[i][j - 1].val + 1;
          diag_val = m[i - 1][j - 1].val + (str1[j - 1] == str2[i - 1] ? 0 : 1);
          break;
        // Different formula for shared substr
        case shared_substr_mat:
          up_val = m[i - 1][j].val;
          left_val = m[i][j - 1].val;
          diag_val = m[i - 1][j - 1].val + (str1[j - 1] == str2[i - 1] ? 1 : 0);
          break;
        default:
          return;
      }
      size_t res = comp_func(up_val, left_val, diag_val);
      m[i][j].val = res;

      // Set which Operations can be used
      m[i][j].up = res == up_val;
      m[i][j].left = res == left_val;
      m[i][j].diag = res == diag_val;
    }
  }
}


/**
 * Print the matrix with the solution paths
 */
void print_str_matrix(char *str1, char *str2, matrix m) {
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);
  printf("    ");
  for (size_t i = 0; i <= len1; i++) {
    printf("   %c", str1[i]);
  }
  printf("\n   ");
  for (size_t i = 0; i <= len2; i++) {
    for (size_t j = 0; j <= len1; j++) {
      if (m[i][j].left) {
        printf(" ← ");
      } else if (j != 0) {
        printf("   ");
      }
      printf("%zu", m[i][j].val);
    }
    printf("\n");
    for (size_t j = 0; j <= len1 && i != len2; j++) {
      if (m[i + 1][j].diag) {
        printf(" ↖ ");
      } else {
        printf("   ");
      }
      if (m[i + 1][j].up) {
        printf("↑");
      } else {
        printf(" ");
      }
    }
    if (i != len2) {
      printf("\n");
      printf("%c  ", str2[i]);
    }
  }
}

void print_edit_sequences(char *str1, char *str2, matrix_t mat_type) {
  char paths[MAX_SIZE][MAX_SIZE] = {{'\0'}};
  matrix m;
  // For the fuzzy search, the beginning of the matching substring in str1
  size_t substr_start = 0;
  size_t len2 = strlen(str2);
  size_t len1 = strlen(str1);
  size_t index = 0;
  size_t *index_p = &index;

  build_str_matrix(str1, str2, m, mat_type);
  print_str_matrix(str1, str2, m);

  if (mat_type == fuzzy_search_mat) {
    len1 = get_minimum_index(m[len2], len1 + 1);
    substr_start = (len1 - len2);
  }

  size_t max = build_str_matrix_reverse_edit_sequences(
      str1, str2, len2, len1, substr_start, index_p, paths, m);
  for (size_t i = 0; i <= max; i++) {
    // Reverse the seq
    size_t path_len = revstr(paths[i]);
    // Output of str1
    printf("\nw|");
    print_str_except_on_operation(str1, paths[i], insert, substr_start);

    // output str2
    printf("\nv|");
    print_str_except_on_operation(str2, paths[i], delete, 0);

    // separator
    printf("\n--");
    for (size_t j = 0; j < path_len; j++) {
      printf("-");
    }

    // print edit sequence
    printf("\n |");
    printf("%s", paths[i]);
    printf("\n");
  }
}

static size_t get_minimum_index(levenshtein_rec array[], size_t len) {
  size_t min = array[0].val;
  size_t index = 0;
  for (size_t i = 1; i < len; i++) {
    if (array[i].val < min) {
      min = array[i].val;
      index = i;
    }
  }
  return index;
}

/**
 * Prints a string character for character,
 * but prints a blank if a character of the levenshtein_seq
 * at the index j matches the operation
 */
static void
print_str_except_on_operation(char *str, const char *levenshtein_seq,
                              operations op, size_t start) {
  //size_t length = strlen(levenshtein_seq);
  for (size_t j = 0, k = start; j < strlen(levenshtein_seq); j++) {
    if (levenshtein_seq[j] == (char) op) {
      printf(" ");
    } else {
      printf("%c", str[k]);
      k++;
    }
  }
}

/**
 * build a array of string, with each line containing the reverse levenshtein edit sequence
 * @return the last index used
 */
static size_t
build_str_matrix_reverse_edit_sequences(char *str1, char *str2,
                                        size_t row, size_t col,
                                        size_t end_col, size_t *index,
                                        char paths[][100], matrix m) {
  // Recursion floor
  if (row == 0 && col == end_col) {
    return *index;
  }
  bool changed = false;
  char tmp[MAX_SIZE] = {'\0'};
  strcpy(tmp, paths[*index]);
  levenshtein_rec lev_el = m[row][col];

  if (lev_el.up) {
    strcat_char(paths[*index], insert);
    build_str_matrix_reverse_edit_sequences(
        str1, str2, row - 1, col, end_col, index, paths, m);
    changed = true;
  }

  if (lev_el.left) {
    if (changed) {
      (*index)++;
      strcpy(paths[*index], tmp);
    } else {
      changed = true;
    }
    strcat_char(paths[*index], delete);
    build_str_matrix_reverse_edit_sequences(
        str1, str2, row, col - 1, end_col, index, paths, m);
  }
  if (lev_el.diag) {
    if (changed) {
      (*index)++;
      strcpy(paths[*index], tmp);
    }
    strcat_char(paths[*index], str1[col - 1] == str2[row - 1] ? noop : change);
    build_str_matrix_reverse_edit_sequences(
        str1, str2, row - 1, col - 1, end_col, index, paths, m);
  }
  return *index;
}

/**
 * Initialize the matrix to calculate longest shared seq.
 * It just makes sure that the first row and first column consists of zeros.
 */
static void init_longest_shared_substr_matrix(const size_t num_of_cols,
                                              const size_t num_of_rows, matrix m) {
  m[0][0].val = 0;
  m[0][0].up = false;
  m[0][0].left = false;
  m[0][0].diag = false;
  size_t max = num_of_cols > num_of_rows ? num_of_cols : num_of_rows;
  for (size_t i = 1; i <= max; i++) {
    if (i <= num_of_rows) {
      m[i][0].val = 0;
      m[i][0].up = true;
      m[i][0].left = false;
      m[i][0].diag = false;
    }
    if (i <= num_of_cols) {
      m[0][i].val = 0;
      m[0][i].up = false;
      m[0][i].left = true;
      m[0][i].diag = false;
    }
  }
}

/**
 * Initialize the matrix to calculate the levenshtein distance
 * The matrix is build with num_of_cols as the number of the columns
 * and num_of_rows for the number of rows
 */
static void init_levenshtein_matrix(const size_t num_of_cols,
                                    const size_t num_of_rows, matrix m) {
  m[0][0].val = 0;
  m[0][0].up = false;
  m[0][0].left = false;
  m[0][0].diag = false;
  size_t max = num_of_cols > num_of_rows ? num_of_cols : num_of_rows;
  for (size_t i = 1; i <= max; i++) {
    if (i <= num_of_rows) {
      m[i][0].val = m[i - 1][0].val + 1;
      m[i][0].up = true;
      m[i][0].left = false;
      m[i][0].diag = false;
    }
    if (i <= num_of_cols) {
      m[0][i].val = m[0][i - 1].val + 1;
      m[0][i].up = false;
      m[0][i].left = true;
      m[0][i].diag = false;
    }
  }
}

/**
 * Initialize the matrix for fuzzy search.
 * Its nearly the same as for levenshtein,
 * but the top row consists of only zeroes
 */
static void init_fuzzy_search_matrix(const size_t num_of_cols,
                                     const size_t num_of_rows, matrix m) {
  m[0][0].val = 0;
  m[0][0].up = false;
  m[0][0].left = false;
  m[0][0].diag = false;
  size_t max = num_of_cols > num_of_rows ? num_of_cols : num_of_rows;
  for (size_t i = 1; i <= max; i++) {
    if (i <= num_of_rows) {
      m[i][0].val = m[i - 1][0].val + 1;
      m[i][0].up = true;
      m[i][0].left = false;
      m[i][0].diag = false;
    }
    if (i <= num_of_cols) {
      m[0][i].val = 0;
      m[0][i].up = false;
      m[0][i].left = true;
      m[0][i].diag = false;
    }
  }
}
