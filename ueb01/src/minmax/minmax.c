#include <stdio.h>
#include <stdlib.h>

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
  int i, curr, min = 0, max = 0;
  for (i = 1; i < argc; i++ ) {
    curr = parse_int(argv[i]);
    if (curr > max) {
      max = curr; 
    } 
    if (curr < min) {
      min = curr; 
    }
  } 
  printf("Min: %d\n", min);
  printf("Max: %i\n", max);
  return 0;
}

