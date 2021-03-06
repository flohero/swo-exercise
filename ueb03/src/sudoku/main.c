#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"

int main(void) {
    /*int grid[] = {5, 3, 0, 0, 7, 0, 0, 0, 0,
                  6, 0, 0, 1, 9, 5, 0, 0, 0,
                  0, 9, 8, 0, 0, 0, 0, 6, 0,
                  8, 0, 0, 0, 6, 0, 0, 0, 3,
                  4, 0, 0, 8, 0, 3, 0, 0, 1,
                  7, 0, 0, 0, 2, 0, 0, 0, 6,
                  0, 6, 0, 0, 0, 0, 2, 8, 0,
                  0, 0, 0, 4, 1, 9, 0, 0, 5,
                  0, 0, 0, 0, 8, 0, 0, 7, 9};*/
    /*int grid[] = {8, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 3, 6, 0, 0, 0, 0, 0,
                  0, 7, 0, 0, 9, 0, 2, 0, 0,
                  0, 5, 0, 0, 0, 7, 0, 0, 0,
                  0, 0, 0, 0, 4, 5, 7, 0, 0,
                  0, 0, 0, 1, 0, 0, 0, 3, 0,
                  0, 0, 1, 0, 0, 0, 0, 6, 8,
                  0, 0, 8, 5, 0, 0, 0, 1, 0,
                  0, 9, 0, 0, 0, 0, 4, 0 ,0};*/
//Input grid
    int grid[] = {0, 0, 0, 6, 0, 0, 4, 0, 0,
                  7, 0, 0, 0, 0, 3, 6, 0, 0,
                  0, 0, 0, 0, 9, 1, 0, 8, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 5, 0, 1, 8, 0, 0, 0, 3,
                  0, 0, 0, 3, 0, 6, 0, 4, 5,
                  0, 4, 0, 2, 0, 0, 0, 6, 0,
                  9, 0, 3, 0, 0, 0, 0, 0, 0,
                  0, 2, 0, 0, 0, 0, 1, 0, 0};
    clock_t start_t, end_t, total_t;
    start_t = clock();
    sudoku(grid);
    end_t = clock();
    total_t = (end_t - start_t);
    printf("\nStart time %ld\n", start_t);
    printf("End time %ld\n", end_t);
    printf("Total time taken: %ld\n", total_t);
    return EXIT_SUCCESS;
}
