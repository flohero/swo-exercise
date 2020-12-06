//
// Created by florian on 01.12.20.
//

#include "../render.h"
#include <stdlib.h>
#include "block_types.h"

/**
 * Add to degrees together,
 * if it is over 360° or under 0° it will loop back
 * @returns between 0° and exclusive 360°
 */
extern degrees_of_90 add(degrees_of_90 left, degrees_of_90 right) {
  return (left + right + d360) % d360;
}

/**
 * @returns a random block_type
 */
extern block_type random_block_type(void) {
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

/**
 * Render a mino
 */
extern void render_mino(mino m) {
  render_quad(m.pos, m.color);
}
