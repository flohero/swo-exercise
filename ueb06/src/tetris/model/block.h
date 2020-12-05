#ifndef BLOCK_H
#define BLOCK_H

#include <assert.h>
#include <stdbool.h>
#include "block_types.h"

#define MINOS_PER_BLOCK 4

// aka tetrimino
typedef struct block block;

typedef position (*position_func)(block, int);

struct block {
  position pos;
  color color;
  block_type type;
  degrees_of_90 orientation;
  position_func position_func;
};

extern void render_block(block block);

extern block new_block();

#endif
