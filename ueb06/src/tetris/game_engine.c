#include <stdio.h>
#include <GLFW/glfw3.h>
#include "game_engine.h"
#include "current_block.h"
#include "game_board.h"
#include "timer.h"
#include "saved_block.h"

#define LEVEL_FACTOR 10

#define POINTS_PER_ROW 100

#define POINTS_PER_CONTINOUS_TETRIS 1200

#define POINTS_PER_TETRIS 800

static bool game_over = false;
static int points = 0;
static int lines_cleared = 0;
static bool is_tetris = false;
static bool paused = false;
static bool can_switch = true;

static void calculate_points(int rows);

static int calculate_level(void);

static void pause(void);

static void print_stats(void);

extern bool ge_handle_move(int dx, int dy, degrees_of_90 deg) {
  if (game_over) {
    return false;
  }
  // If the block cant drop anymore,
  // its at the bottom and a new block is being spawned
  if (!cb_try_move(dx, dy, deg) && dy == -1) {
    block current = cb_get_block();
    gb_add_block(current);
    current = cb_new_block();

    // If the block filled up any rows, delete them
    int deleted_lines = gb_delete_lines();

    // For the level calculation
    lines_cleared += deleted_lines;
    calculate_points(deleted_lines);

    // print stats like points and level
    print_stats();

    // Allow the player to switch the saved block with the current block
    can_switch = true;

    // Check if the current block is at an valid position
    // if not  that means that the board is filled up
    if (!gb_is_valid_position(current)) {
      game_over = true;
    }
  }
  return ge_is_game_over();
}


/**
 * @returns if the game is over
 */
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
  sb_delete_saved_block();
}

/**
 * get the current level
 */
extern int get_level(void) {
  return calculate_level();
}

/**
 * Key event listener, used by GLFW
 */
extern void ge_on_key(GLFWwindow *window, int key, int scancode, int action, int modes) {
  int dx = 0, dy = 0;
  degrees_of_90 deg = d0;
  switch (key) {
    // Drop down faster
    case GLFW_KEY_J:
    case GLFW_KEY_S:
      dy = -1;
      break;
      // Move block to the left
    case GLFW_KEY_H:
    case GLFW_KEY_A:
      dx = -1;
      break;
      // Move block to the right
    case GLFW_KEY_L:
    case GLFW_KEY_D:
      dx = 1;
      break;
      // Rotate block counterclockwise
    case GLFW_KEY_Q:
      deg = d90;
      break;
      // Rotate block clockwise
    case GLFW_KEY_E:
      deg = d90neg;
      break;
      // Save current block
    case GLFW_KEY_C:
      if (action == GLFW_PRESS && can_switch && !paused) {
        block new_current_block = sb_switch_saved_block(cb_get_block());
        cb_set_block(new_current_block);
        can_switch = false;
      }
      return;
      // Hard drop current block
    case GLFW_KEY_SPACE:
      if (action == GLFW_PRESS && !paused) {
        while (cb_try_move(0, -1, d0));
        return;
      }
      // Pause game
    case GLFW_KEY_ESCAPE:
      if (action == GLFW_PRESS) {
        pause();
      }
      return;
    default:
      return;
  }
  if (paused) {
    return;
  }
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    if (ge_handle_move(dx, dy, deg)) {
      printf("Game Over\n");
      // If the game is over, reset the engine and the board
      ge_reset();
    }
  }
}

static void calculate_points(int rows) {
  points += rows == MINOS_PER_BLOCK
            ? (is_tetris ? POINTS_PER_CONTINOUS_TETRIS : POINTS_PER_TETRIS)
            : rows * POINTS_PER_ROW;
  is_tetris = rows == MINOS_PER_BLOCK;
}

static int calculate_level(void) {
  return lines_cleared / LEVEL_FACTOR;
}

static void pause(void) {
  if (paused) {
    timer_resume();
  } else {
    timer_stop();
  }
  paused = !paused;
}

static void print_stats(void) {
  printf("Points: %d\n", points);
  printf("Level: %d\n", calculate_level());
}
