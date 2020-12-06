#include <stddef.h>
#include <assert.h>
#include "game_board.h"
#include "saved_block.h"
#include "render.h"
#include "model/block_types.h"

#define MAX_BLOCKS_COUNT ((GB_ROWS)*(GB_COLS))

// array to save all placed minos
static mino minos[MAX_BLOCKS_COUNT];
// Saves count of minos
static size_t mino_counter = 0;

static void delete_row(int row);

static void shift_minos(int row);

/**
 * Checks if a block is on a valid position on the gameboard
 * @param block block on gameboard
 * @returns if the block is on a valid position on the gameboard
 */
extern bool gb_is_valid_position(const block block) {
  for (int i = 0; i < MINOS_PER_BLOCK; i++) {
    position pos = block.position_func(block, i);
    if (!(pos.x >= 0 && pos.x < GB_COLS &&
          pos.y >= 0 && pos.y < GB_ROWS)) {
      return false;
    }
    // check collision
    for (size_t j = 0; j < mino_counter; j++) {
      if (minos[j].pos.x == pos.x &&
          minos[j].pos.y == pos.y) {
        return false;
      }
    }
  }
  return true;
}

/**
 * Add a block to the gameboard.
 * The block is being converted to minos
 * @param block block to be added to the gameboard
 */
extern void gb_add_block(const block block) {
  assert(gb_is_valid_position(block));
  assert(mino_counter < MAX_BLOCKS_COUNT);
  for (int i = 0; i < MINOS_PER_BLOCK; i++) {
    mino t = {
        .pos = block.position_func(block, i),
        .color = block.color
    };
    minos[mino_counter++] = t;
  }
}

/**
 * Render the gameboard and its minos
 */
extern void gb_render(void) {
  for(int i = 0; i < GB_ROWS; i++) {
    position pos = {.x = GB_COLS, .y = i};
    render_quad(pos, color_white);
  }
  sb_render_saved_block();
  for (size_t i = 0; i < mino_counter; i++) {
    render_mino(minos[i]);
  }
}

/**
 * Delete all filled up rows
 * @returns count of deleted rows
 */
extern int gb_delete_lines(void) {
  size_t i = 0;
  int deleted_rows = 0;
  while (i < mino_counter) {
    mino t = minos[i];
    int tetrimino_row = 0;
    // count minos in the same row
    for (size_t j = 0; j < mino_counter && tetrimino_row != GB_COLS; j++) {
      if (t.pos.y == minos[j].pos.y) {
        tetrimino_row++;
      }
    }

    if (tetrimino_row == GB_COLS) {
      // Delete model if on the same row
      delete_row(t.pos.y);
      shift_minos(t.pos.y);
      deleted_rows++;
    } else {
      i++;
    }
  }
  return deleted_rows;
}

/**
 * Delete a single specified row
 * @param row row to be deleted
 */
static void delete_row(const int row) {
  size_t i = 0;
  while (i < mino_counter) {
    // Delete the block
    if (row == minos[i].pos.y) {
      for (size_t j = (i + 1); j < mino_counter; j++) {
        minos[j - 1] = minos[j];
      }
      mino_counter--;
    } else {
      i++;
    }
  }
}

/**
 * Change y-position of all minos above a specified row by one
 * @param row
 */
static void shift_minos(const int row) {
  for (size_t i = 0; i < mino_counter; i++) {
    if (minos[i].pos.y > row) {
      minos[i].pos.y--;
    }
  }
}

/**
 * Reset the gameboard, should be used with ge_reset
 */
extern void gb_reset(void) {
  mino_counter = 0;
}
