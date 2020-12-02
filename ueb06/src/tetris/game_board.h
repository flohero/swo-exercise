#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <stdbool.h>
#include "model/block.h"

#define GB_ROWS 22
#define GB_COLS 11

extern bool gb_is_valid_position(block block);

extern void gb_add_block(block block);

extern void gb_render(void);

extern void gb_reset(void);

extern int gb_delete_lines(void);

extern int get_level(void);

#endif
