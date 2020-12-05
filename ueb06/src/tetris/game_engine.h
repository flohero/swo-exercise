#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdbool.h>
#include "model/block.h"

extern bool ge_handle_move(int dx, int dy, degrees_of_90 degree_of_90);

extern bool ge_is_game_over(void);

extern void ge_reset(void);

extern void ge_on_key(GLFWwindow *window, int key, int scancode, int action, int modes);

#endif
