#include <assert.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "timer.h"
#include "game_board.h"

static double interval = 1.0;
static timer_func callback = NULL;
static bool timer_running = false;

static void reset_time(void);

/**
 * Start the timer
 * @param itvl timer interval
 * @param on_tick callback function
 */
extern void timer_start(double itvl, timer_func on_tick) {
  assert(on_tick != NULL);
  assert(itvl > 0);

  interval = itvl;
  callback = on_tick;
  timer_running = true;

  reset_time();
}

/**
 * Run the callback function, if the interval is correct
 */
extern void timer_fire(void) {
  if (!timer_running) {
    return;
  }
  int new_pace = STANDARD_PACE - (get_level() * 5);
  int res = new_pace > 1 ? new_pace : 1;
  if (glfwGetTime() >= (interval / FRAMES_PER_SECOND) * res) {
    callback();
    reset_time();
  }
}

/**
 * Pause timer
 */
extern void timer_stop(void) {
  timer_running = false;
}

/**
 * Resume Timer
 */
extern void timer_resume(void) {
  timer_running = true;
}

/**
 * reset timer to zero
 */
static void reset_time(void) {
  glfwSetTime(0.0);
}
