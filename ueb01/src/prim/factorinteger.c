#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void prime_factorization(int n) {
  int i, count = 0; 
  printf("{");

  /* Check for special cases */
  if (n == 0) {
    printf("{0,1}}\n");
    return;
  }
  if (n == 1) {
    printf("{1,1}}\n");
    return;
  }
  /* Check for even numbers beforehand */
  while (n % 2 == 0) {
    n = n / 2;
    count++;
  }
  if (count > 0) {
    printf("{2,%d},", count);
  }
  /* Skip 0 - 2, since these cases were already checked at the beginning of this function */
  for (i = 3; i <= sqrt(n); i += 2) {
    count = 0;
    /* While n is divided increase counter */
    while (n % i == 0) {
      n = n / i;
      count++;
    }
    if (count > 0) {
      printf("{%d,%d},", i, count);
    }
  }
  /* If n is greater than 2 it is a primenumber */
  if (n > 2) {
    printf("{%d,1}", n);
  }
  printf("}\n");
}

/* Parse an int and check if it was parsed succesfully */
int parse_int(char *c) {
  int status, parsed;
  status = sscanf(c, "%d", &parsed);
  /* If status != 1 the string wasn't parsed successfully */ 
  if(status == 1) {
    return parsed;
  } 
  printf("%s is not an int\n", c);
  exit(1);
}

int main(int argc, char *argv[]) {
  int i;
  long unsigned int column_width = 0;

  /* Calculate column width */
  for (i = 1; i < argc; i++) {
    if (strlen(argv[i]) > column_width) {
      column_width = strlen(argv[i]);
    }
  }
  for (i = 1; i < argc; i++) {
    int curr = parse_int(argv[i]);
    if (curr < 0) {
      printf("The numbers should be positive");
      return 1;
    }
    printf("%*i: ", (int)column_width, curr);
    prime_factorization(curr);
  }
  return 0;
}

