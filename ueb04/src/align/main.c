#include <stdlib.h>
#include <stdio.h>
#include "align.h"


void levenshtein_test_cases() {
  printf("\nLEVENSHTEIN-TEST-CASES\n");
  // No same character at the same index
  print_levenshtein_edit_sequences("AUN", "INU");

  // Test Case from the specification
  print_levenshtein_edit_sequences("TGCATA", "ATCTGAT");

  // Only one mismatch
  print_levenshtein_edit_sequences("hello", "hallo");

  // No matching character and different length
  // Every operation should be a change, but one should be an insert
  print_levenshtein_edit_sequences("asdf", "ghjkl");
  // Every operation should be a change, but one should be a delete
  print_levenshtein_edit_sequences("ghjkl", "asdf");
}

void longest_shared_subs_str_test_cases() {
  printf("\nLONGEST-SHARED-SUBSTRING-TEST-CASES\n");
  // No same character at the same index
  print_longest_shared_substr("AUN", "INU");

  // Test Case from the specification
  print_longest_shared_substr("TGCATA", "ATCTGAT");

  // Only one mismatch
  print_longest_shared_substr("hello", "hallo");

  // No matching character and different length
  // Not a good idea, resulting output is over 7000 lines long
  print_longest_shared_substr("asdf", "ghjkl");
}

void fuzzy_search_test_cases() {
  printf("\nFUZZY_SEARCH-TEST-CASES\n");
  // Test Case from the specification
  print_fuzzy_search("SVLQDRSMPHQEILAADEVLQESEMRQQDMISHDE", "EIQADEVRL");

  // *According* to the Specification only one best match needs to be found
  // Here are 2 best matches, but only the first one will be used.
  print_fuzzy_search("TOST------TASTE", "TEST");

  // Simple test case
  print_fuzzy_search("Lorem ipsum dolor sit amet", "colour");

  //
  print_fuzzy_search("Pie Jesu Domine, Dona eis requiem", "Pi Jesus");
}

int main(void) {
  levenshtein_test_cases();
  longest_shared_subs_str_test_cases();
  fuzzy_search_test_cases();
  /*
  print_longest_shared_substr("TGCATA", "ATCTGAT");
  print_levenshtein_edit_sequences("TGCATA", "ATCTGAT");
  printf("fuzzy search\n");
  print_fuzzy_search("SVLQDRSMPHQEILAADEVLQESEMRQQDMISHDE", "EIQADEVRL");*/
  return EXIT_SUCCESS;
}


