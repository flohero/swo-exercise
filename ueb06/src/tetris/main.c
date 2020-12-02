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
#define TIMER_INTERVAL 0.5


static void window_initialized(GLFWwindow *window);

static void render_window(void);

static void on_key(GLFWwindow *window, int key, int scancode, int action, int modes);

static void on_tick(void);

static void window_initialized(GLFWwindow *window) {
  glfwSetKeyCallback(window, on_key);
  timer_start(TIMER_INTERVAL, on_tick);
}

static void on_key(GLFWwindow *window, int key, int scancode, int action, int modes) {

  int dx = 0, dy = 0;
  degrees_of_90 deg = d0;
  switch (key) {
    case GLFW_KEY_J:
    case GLFW_KEY_S:
      dy = -1;
      break;
    case GLFW_KEY_H:
    case GLFW_KEY_A:
      dx = -1;
      break;
    case GLFW_KEY_L:
    case GLFW_KEY_D:
      dx = 1;
      break;
    case GLFW_KEY_Q:
      deg = d90neg;
      break;
    case GLFW_KEY_E:
      deg = d90;
      break;
    case GLFW_KEY_SPACE:
      if (action == GLFW_PRESS) {
        while (cb_try_move(0, -1, d0));
        return;
      }
    default:
      return;
  }
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    if (ge_handle_move(dx, dy, deg)) {
      printf("Game Over");
      ge_reset();
      //timer_stop();
    }
  }
}

static void on_tick(void) {
  on_key(NULL, GLFW_KEY_S, 0, GLFW_PRESS, 0);
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
    glScalef((float) width / (float) GB_COLS, (float) height / (float) GB_ROWS,
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
