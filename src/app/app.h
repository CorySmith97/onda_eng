//
// Created by Cory Smith on 7/25/25.
//

#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <epoxy/gl.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../core/core.h"

typedef enum {
    backend_vulkan,
    backend_opengl,
} Backend;

typedef enum {
    KEY_ESCAPE,
    KEY_ENTER,
    KEY_SPACE,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    KEY_HOME,
    KEY_END,
    KEY_INSERT,
    KEY_DELETE,
    KEY_HELP,
    KEY_LAST,
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR,
    KEY_FIVE,
    KEY_SIX,
    KEY_SEVEN,
    KEY_EIGHT,
    KEY_NINE,
} Keys;

typedef struct App {
    GLFWwindow* window;
    i32 width;
    i32 height;
    f64 mouse_x;
    f64 mouse_y;
} App;

extern void app_init(App* app, Backend);
extern void app_run(App* app);
extern bool app_should_close(App* app);
extern void app_deinit(App* app);

extern bool app_is_key_pressed(Keys key);
extern Vec2 app_get_mouse_position(App* app);

#endif //APP_H
