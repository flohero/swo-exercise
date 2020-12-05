//
// Created by florian on 05.12.20.
//

#include <assert.h>
#include "render.h"
#include "model/block_types.h"
#include "game_board.h"


extern void render_quad(const position pos, const color color) {
  static_assert(sizeof(color) == 4, "detected unexpected size for colors");

  glColor3ubv((unsigned char *) &color);

  glBegin(GL_QUADS);
  glVertex2i(pos.x, pos.y);
  glVertex2i(pos.x, pos.y + 1);
  glVertex2i(pos.x + 1, pos.y + 1);
  glVertex2i(pos.x + 1, pos.y);
  glEnd();
}
