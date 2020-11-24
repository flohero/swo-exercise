#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"

/**
 * primitive function to log errors
 */
void log_error(error_type error, const char *func_name, const int line) {
  switch (error) {
    case out_of_memory:
      printf("Ran out of memory");
      break;
    case node_doesnt_exist:
      printf("Node doesn't exist");
      break;
    case node_already_exists:
      printf("Node already exists");
      break;
    case edge_already_exists:
      printf("Edge already exists");
      break;
    case null_pointer:
      printf("Element was a null pointer");
      break;
    case cyclic_graph:
      printf("Graph is cyclic");
      break;
    default:
      return;
  }
  printf(" in %s near the line: %d\n", func_name, line);
}

void exit_on_mem_error(bool expr, const char *func_name, int line) {
  if (expr) {
    log_error(out_of_memory, func_name, line);
    exit(1);
  }
}
