#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>

#include "model/block.h"
#include "current_block.h"
#include "game_board.h"
#include "game_engine.h"
#include "timer.h"

#define WIDTH  400
#define HEIGHT ((WIDTH * GB_ROWS) / GB_COLS)
#define TIMER_INTERVAL 1.0

static void window_initialized(GLFWwindow *window);

static void render_window(void);

static void on_tick(void);

static void window_initialized(GLFWwindow *window) {
  glfwSetKeyCallback(window, ge_on_key);
  timer_start(TIMER_INTERVAL, on_tick);
}

static void on_tick(void) {
  if (ge_handle_move(0, -1, d0)) {
    printf("Game Over\n");
    // If the game is over, reset the engine and the board
    ge_reset();
  }
}

static void render_window(void) {
  timer_fire();
  gb_render();
  cb_render();
}

int main() {
  if (!glfwInit()) {
    fprintf(stderr, "could not initialize GLFW\n");
    return EXIT_FAILURE;
  }
  srand((unsigned) time(NULL));
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tetris", NULL, NULL);
  if (!window) {
    glfwTerminate();
    fprintf(stderr, "could not open window\n");
    return EXIT_FAILURE;
  }

  int width, height;
  glfwGetWindowSize(window, &width, &height);
  glfwSetWindowAspectRatio(window, width, height); //enforce correct aspect ratio
  glfwMakeContextCurrent(window);

  window_initialized(window);

  while (!glfwWindowShouldClose(window)) {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT); //clear frame buffer
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height); //orthogonal projection - origin is in lower-left corner
    glScalef((float) width / ((float) GB_COLS + GB_SIDE_WIDTH), (float) height / (float) GB_ROWS,
             1); //scale logical pixel to screen pixels

    render_window();

    const GLenum error = glGetError();
    if (error != GL_NO_ERROR) fprintf(stderr, "ERROR: %s\n", gluErrorString(error));

    glfwSwapBuffers(window);//push image to display
    // glfwPollEvents();
    glfwWaitEventsTimeout(TIMER_INTERVAL / 5); //process all events of the application
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
