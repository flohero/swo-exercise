#include <stddef.h>
#include <assert.h>
#include "game_board.h"
#include "sb_saved_block.h"
#include "render.h"

#define MAX_BLOCKS_COUNT ((GB_ROWS)*(GB_COLS))

static mino tetriminos[MAX_BLOCKS_COUNT];
static size_t tetrimino_counter = 0;

static void delete_row(int row);

static void shift_tetriminos(int row);

bool gb_is_valid_position(const block block) {
  for (int i = 0; i < MINOS_PER_BLOCK; i++) {
    position pos = block.position_func(block, i);
    if (!(pos.x >= 0 && pos.x < GB_COLS &&
          pos.y >= 0 && pos.y < GB_ROWS)) {
      return false;
    }
    // check collision
    for (size_t j = 0; j < tetrimino_counter; j++) {
      if (tetriminos[j].pos.x == pos.x &&
          tetriminos[j].pos.y == pos.y) {
        return false;
      }
    }
  }
  return true;
}

extern void gb_add_block(const block block) {
  assert(gb_is_valid_position(block));
  assert(tetrimino_counter < MAX_BLOCKS_COUNT);
  for (int i = 0; i < MINOS_PER_BLOCK; i++) {
    mino t = {
        .pos = block.position_func(block, i),
        .color = block.color
    };
    tetriminos[tetrimino_counter++] = t;
  }
}

extern void gb_render(void) {
  for(int i = 0; i < GB_ROWS; i++) {
    position pos = {.x = GB_COLS, .y = i};
    render_quad(pos, color_white);
  }
  sb_render_saved_block();
  for (size_t i = 0; i < tetrimino_counter; i++) {
    render_tetrimino(tetriminos[i]);
  }
}

extern int gb_delete_lines(void) {
  size_t i = 0;
  int deleted_rows = 0;
  while (i < tetrimino_counter) {
    mino t = tetriminos[i];
    int tetrimino_row = 0;
    // count tetriminos in the same row
    for (size_t j = 0; j < tetrimino_counter && tetrimino_row != GB_COLS; j++) {
      if (t.pos.y == tetriminos[j].pos.y) {
        tetrimino_row++;
      }
    }

    if (tetrimino_row == GB_COLS) {
      // Delete model if on the same row
      delete_row(t.pos.y);
      shift_tetriminos(t.pos.y);
      deleted_rows++;
    } else {
      i++;
    }
  }
  return deleted_rows;
}

static void delete_row(const int row) {
  size_t i = 0;
  while (i < tetrimino_counter) {
    // Delete the block
    if (row == tetriminos[i].pos.y) {
      for (size_t j = (i + 1); j < tetrimino_counter; j++) {
        tetriminos[j - 1] = tetriminos[j];
      }
      tetrimino_counter--;
    } else {
      i++;
    }
  }
}

static void shift_tetriminos(const int row) {
  for (size_t i = 0; i < tetrimino_counter; i++) {
    if (tetriminos[i].pos.y > row) {
      tetriminos[i].pos.y--;
    }
  }
}

/**
 * Reset the gameboard, should be used with ge_reset
 */
extern void gb_reset(void) {
  tetrimino_counter = 0;
}
