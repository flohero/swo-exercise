//
// Created by florian on 01.12.20.
//

#ifndef SWO3_BLOCK_TYPES_H
#define SWO3_BLOCK_TYPES_H

#include <assert.h>
#include <stdbool.h>

typedef enum {
  color_black = 0x000000U,
  color_red = 0x0000FFU,
  color_green = 0x00FF00U,
  color_blue = 0xFF0000U,
  color_yellow = color_red | color_green,
  color_magenta = color_red | color_blue,
  color_cyan = color_green | color_blue,
  color_white = color_red | color_green | color_blue,
  color_orange = 0x008ddeU
} color;

typedef enum {
  i_block = 'I',
  j_block = 'J',
  l_block = 'L',
  o_block = 'O',
  s_block = 'S',
  z_block = 'Z',
  t_block = 'T'
} block_type;

typedef enum {
  d0 = 0,
  d90 = 90,
  d90neg = -90,
  d180 = 180,
  d270 = 270,
  d360 = 360
} degrees_of_90;

typedef struct {
  int x, y;
} position;

typedef struct {
  position pos;
  color color;
} mino;

degrees_of_90 add(degrees_of_90 left, degrees_of_90 right);

block_type random_block_type(void);

extern void render_mino(mino m);


#endif //SWO3_BLOCK_TYPES_H
