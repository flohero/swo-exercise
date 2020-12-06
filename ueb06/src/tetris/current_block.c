#include <stdlib.h>
#include "current_block.h"
#include "game_board.h"
#include "model/block.h"

// the current block, with some standard values, which will be overwritten
static block current =
    {{.x = GB_COLS / 2, .y = GB_ROWS - 1}, .color = color_red};

/**
 * Try to move or rotate the current block by dx, dy and rotationfactor deg
 * @returns if the function was successful
 */
extern bool cb_try_move(int dx, int dy, degrees_of_90 deg) {
  block transient_block = current;
  transient_block.pos.x += dx;
  transient_block.pos.y += dy;
  transient_block.orientation = add(transient_block.orientation, deg);

  if (!gb_is_valid_position(transient_block)) {
    return false;
  }
  current.pos = transient_block.pos;
  current.orientation = transient_block.orientation;
  return true;
}

/**
 * Render current block
 */
extern void cb_render(void) {
  if (current.position_func == NULL) {
    current = cb_new_block();
  }
  render_block(current);
}

/**
 * Generate new current block
 * @returns the current block
 */
extern block cb_new_block(void) {
  current = new_block();
  return current;
}

/**
 * @returns current block
 */
extern block cb_get_block(void) {
  return current;
}

/**
 * Replace current block by block
 * @param block new block
 */
extern void cb_set_block(block block) {
  current = block;
}



