#include <assert.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "timer.h"
#include "game_board.h"

static double interval = 1.0;
static timer_func callback = NULL;
static bool timer_running = false;

static void reset_time(void);

extern void timer_start(double itvl, timer_func on_tick) {
  assert(on_tick != NULL);
  assert(itvl > 0);

  interval = itvl;
  callback = on_tick;
  timer_running = true;

  reset_time();
}

extern void timer_fire(void) {
  if (!timer_running) {
    return;
  }
  int res = 48 - get_level() > 1 ? 48 - get_level() : 1;
  if (glfwGetTime() >= (interval / 60) * res) {
    callback();
    reset_time();
  }
}

extern void timer_stop(void) {
  timer_running = false;
}

extern void timer_resume(void) {
  timer_running = true;
}

static void reset_time(void) {
  glfwSetTime(0.0);
}
