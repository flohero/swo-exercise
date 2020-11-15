#include <stdio.h>
#include <stdbool.h>
#include "sudoku.h"

static bool sudoku_rec(int *grid, int index);

static bool is_safe_to_assign(const int *grid, int index, int num);

static void print_sudoku(const int *grid);

void sudoku(int grid[]) {
    if(sudoku_rec(grid, 0)) {
        print_sudoku(grid);
    } else {
        printf("No solution found!\n");
    }
}

static bool sudoku_rec(int *grid, int index) {
    if (index >= FIELD_COUNT) {
        return true;
    }
    if (grid[index] > 0) {
        return sudoku_rec(grid, index + 1);
    }
    for (int num = 1; num <= ROW_SIZE; num++) {
        if (is_safe_to_assign(grid, index, num)) {
            grid[index] = num;
            if (sudoku_rec(grid, index + 1)) {
                return true;
            }
        }
        grid[index] = 0;
    }
    return false;
}

/**
 * Checks the validity of the numbers in a sudoku.
 * It does NOT check if a sudoku is valid, since a valid sudoku has only one solution.
 * It checks if there are the same numbers in a row, column or cell.
 * @param grid
 * @return if the numbers are correct in the sudoku
 */
static bool is_safe_to_assign(const int *grid, int const index, int const num) {
    int row = index / ROW_SIZE;
    int column = index % ROW_SIZE;
    for (int i = 0; i < FIELD_COUNT; i++) {
        int i_row = i / ROW_SIZE;
        if (row == i_row && grid[i] == num) {
            return false;
        }
        if (i % ROW_SIZE == index % ROW_SIZE && grid[i] == num) {
            return false;
        }
    }

    int row_start = row - row % CELL_SIZE;
    int row_end = row_start + CELL_SIZE;
    int column_start = column - column % CELL_SIZE;
    int column_end = column_start + CELL_SIZE;
    for (int i = row_start; i < row_end; i++) {
        for (int j = column_start; j < column_end; j++) {
            if (grid[j + i * ROW_SIZE] == num) {
                return false;
            }
        }
    }
    return true;
}

static void print_sudoku(const int *grid) {
    for (int i = 0; i < FIELD_COUNT; i++) {
        if (i % 9 == 0) {
            printf("\n");
        }
        printf(" %d ", grid[i]);
    }
}
