#include <stdlib.h>
#include "current_block.h"
#include "game_board.h"
#include "model/block.h"

static block current =
    {{.x = GB_COLS / 2, .y = GB_ROWS - 1}, .color = color_red};


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

extern void cb_render(void) {
  if (current.position_func == NULL) {
    current = cb_new_block();
  }
  render_block(current);
}

extern block cb_new_block(void) {
  current = new_block();
  return current;
}

extern block cb_get_block(void) {
  return current;
}



