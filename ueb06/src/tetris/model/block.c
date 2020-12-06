#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "../game_board.h"
#include "../render.h"
#include "block_types.h"

static position get_pos_of_i_block(block block, int index);

static position get_pos_of_jl_block(block block, int index);

static position get_pos_of_o_block(block block, int index);

static position get_pos_sz_block(block block, int index);

static position get_pos_of_t_block(block block, int index);

static position matrix_rotation(position pos, degrees_of_90 rotate_to);

static position change_block_position_by(position block_pos, position normalized_pos);

/**
 * Render a block with its specified color
 * Optionally print the anchor point of the block
 */
extern void render_block(const block block) {
  for (int i = 0; i < MINOS_PER_BLOCK; i++) {
    position pos = block.position_func(block, i);
    render_quad(pos, block.color);
  }
  //Render anchor of Block
  // For debugging purposes
#ifdef SHOW_ANCHOR
  render_quad(block.pos, color_white  );
#endif
}

/**
 * Generate a new block with standard starting position and orientation
 * The type of the block is random, but its color is defined by the type of the block
 * @returns a new block
 */
extern block new_block() {
  block current;
  current.pos.x = GB_COLS / 2;
  current.pos.y = GB_ROWS - 1;
  current.orientation = d0;
  current.type = random_block_type();
  switch (current.type) {
    case i_block:
      current.position_func = get_pos_of_i_block;
      current.color = color_cyan;
      break;
    case j_block:
      current.color = color_blue;
      current.position_func = get_pos_of_jl_block;
      break;
    case l_block:
      current.color = color_orange;
      current.position_func = get_pos_of_jl_block;
      break;
    case o_block:
      current.color = color_yellow;
      current.position_func = get_pos_of_o_block;
      break;
    case s_block:
      current.color = color_green;
      current.position_func = get_pos_sz_block;
      break;
    case z_block:
      current.color = color_red;
      current.position_func = get_pos_sz_block;
      break;
    case t_block:
      current.color = color_magenta;
      current.position_func = get_pos_of_t_block;
      break;
    default:
      printf("Illegal Block Type");
      exit(EXIT_FAILURE);
  }
  return current;
}

/**
 * Calculate the position of a block,
 * at an index
 * @param block
 * @param index which mino should be calculated
 * @returns the position for an index
 */
static position get_pos_of_i_block(const block block, const int index) {
  position pos = {.x = 0, .y = index};
  pos = matrix_rotation(pos, block.orientation);
  return change_block_position_by(block.pos, pos);
}

/**
 * Calculate the position of a block,
 * at an index
 * @param block
 * @param index which mino should be calculated
 * @returns the position for an index
 */
static position get_pos_of_jl_block(const block block, const int index) {
  bool is_j = block.type == j_block;
  position pos;
  if (index < 3) {
    pos.x = (is_j ? 1 : 0);
    pos.y = index;
  } else {
    pos.x = (is_j ? 0 : 1);
    pos.y = 2;
  }
  pos = matrix_rotation(pos, block.orientation);
  return change_block_position_by(block.pos, pos);
}

/**
 * Calculate the position of a block,
 * at an index
 * @param block
 * @param index which mino should be calculated
 * @returns the position for an index
 */
static position get_pos_of_o_block(const block block, const int index) {
  position pos = {.x = index % 2, .y = index / 2};
  pos = matrix_rotation(pos, block.orientation);
  return change_block_position_by(block.pos, pos);
}

/**
 * Calculate the position of a block,
 * at an index
 * @param block
 * @param index which mino should be calculated
 * @returns the position for an index
 */
static position get_pos_sz_block(const block block, const int index) {
  bool is_s = block.type == s_block;
  int inc1 = is_s ? 0 : 1;
  int inc2 = is_s ? 1 : 0;
  position pos = {
      .x =  index - (index / 2 >= 1 ? 1 : 0),
      .y = (index / 2 >= 1 ? inc1 : inc2)
  };
  pos = matrix_rotation(pos, block.orientation % d180);
  return change_block_position_by(block.pos, pos);
}

/**
 * Calculate the position of a block,
 * at an index
 * @param block
 * @param index which mino should be calculated
 * @returns the position for an index
 */
static position get_pos_of_t_block(const block block, const int index) {
  position pos;
  if (index == MINOS_PER_BLOCK - 1) {
    pos.x = 1;
    pos.y = 0;
  } else {
    pos.x = index;
    pos.y = 1;
  }
  pos = matrix_rotation(pos, block.orientation);
  return change_block_position_by(block.pos, pos);
}

/**
 * Rotate the position by rotate_to
 * @returns the rotated position
 */
static position matrix_rotation(position pos, const degrees_of_90 rotate_to) {
  for (int i = 0; i < (rotate_to / d90); i++) {
    int old_x = pos.x;
    pos.x = -1 * pos.y;
    pos.y = old_x;
  }
  return pos;
}

/**
 * Change the position by another position
 * @returns a new position
 */
static position change_block_position_by(position block_pos, const position normalized_pos) {
  block_pos.x = block_pos.x + normalized_pos.x;
  // Since the anchor point is at the top left of a block
  // the y-axis needs to be subtracted
  block_pos.y = block_pos.y - normalized_pos.y;
  return block_pos;
}
