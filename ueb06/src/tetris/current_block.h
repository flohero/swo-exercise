#ifndef CURRENT_BLOCK_H
#define CURRENT_BLOCK_H

#include "model/block.h"

extern bool cb_try_move(int dx, int dy, degrees_of_90 deg);

extern void cb_render(void);

extern block cb_new_block(void);

extern block cb_get_block(void);

extern void cb_set_block(block block);

#endif
