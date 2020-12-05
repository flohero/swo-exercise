//
// Created by florian on 05.12.20.
//

#include <stdbool.h>
#include "saved_block.h"
#include "model/block.h"
#include "game_board.h"

static block saved_block;
static bool saved = false;

extern bool sb_is_saved(void) {
  return saved;
}

extern void sb_render_saved_block(void) {
  if (saved) {
    render_block(saved_block);
  }
}

/**
 * Set a new block and return old saved block
 */
extern block sb_switch_saved_block(block b) {
  block old_block = saved ? saved_block : new_block();
  saved_block = b;
  old_block.pos.x = GB_COLS / 2;
  old_block.pos.y = GB_ROWS - 1;
  saved_block.pos.x = GB_COLS + 1;
  saved_block.pos.y = GB_ROWS - 1;
  saved = true;
  return old_block;
}

extern void sb_delete_saved_block(void) {
  saved = false;
}
