#include <stdio.h>
#include "game_engine.h"
#include "current_block.h"
#include "game_board.h"

static bool game_over = false;
static int points = 0;
static int lines_cleared = 0;
static bool is_tetris = false;

static void calculate_points(int rows);

static int calculate_level(void);

extern bool ge_handle_move(int dx, int dy, degrees_of_90 deg) {
  if (game_over) {
    return false;
  }
  if (!cb_try_move(dx, dy, deg) && dy == -1) {
    block current = cb_get_block();
    gb_add_block(current);
    current = cb_new_block();
    int deleted_lines = gb_delete_lines();
    lines_cleared += deleted_lines;
    calculate_points(deleted_lines);
    printf("Points: %d\n", points);
    if (!gb_is_valid_position(current)) {
      game_over = true;
    }
  }
  return ge_is_game_over();
}

extern bool ge_is_game_over(void) {
  return game_over;
}

/**
 * Reset the game engine, should be used with gb_reset
 */
extern void ge_reset(void) {
  gb_reset();
  game_over = false;
  points = 0;
  lines_cleared = 0;
  is_tetris = false;
}

extern int get_level(void) {
  return calculate_level();
}

static void calculate_points(int rows) {
  points += rows == MINOS_PER_BLOCK
            ? (is_tetris ? 1200 : 800)
            : rows * 400;
  is_tetris = rows == MINOS_PER_BLOCK;
}

static int calculate_level(void) {
  return lines_cleared / 10;
}
