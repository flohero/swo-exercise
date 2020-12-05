//
// Created by florian on 01.12.20.
//

#include "../render.h"
#include "../game_board.h"
#include "block.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "block_types.h"


degrees_of_90 add(degrees_of_90 left, degrees_of_90 right) {
  return (left + right + d360) % d360;
}

block_type random_block_type(void) {
  static block_type types[] = {
      i_block,
      j_block,
      l_block,
      o_block,
      s_block,
      z_block,
      t_block
  };
  const int n_types = sizeof(types) / sizeof(types[0]);
  return types[rand() % n_types];
}

void render_mino(mino m) {
  render_quad(m.pos, m.color);
}