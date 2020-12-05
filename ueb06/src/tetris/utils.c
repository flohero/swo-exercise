//
// Created by florian on 01.12.20.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

extern void memory_error(bool condition, const char *func, const int line) {
  if (!condition) {
    return;
  }
  printf("Out of memory in %s near line %d", func, line);
  exit(EXIT_FAILURE);
}
