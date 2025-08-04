//
// Created by Cory Smith on 7/25/25.
//

#include "app.h"
#include <GLFW/glfw3.h>


typedef struct Mouse {
} Mouse;

void app_mouse_callback( App *app );

void glfw_error_callback(
    int code,
    const char *des
) {
    LOG(error, "Code: %d, des: %s", code, des);
}

void app_init(
    App* app,
    Backend backend
) {
    glfwInit();
    glfwSetErrorCallback(glfw_error_callback);
    switch (backend) {
    case backend_opengl: {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    } break;
    case backend_vulkan: {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    } break;
    }

    app->width = 1280;
    app->height = 720;
    app->window = glfwCreateWindow(app->width, app->height, "Hello, World!", NULL, NULL);

}

bool app_should_close(App* app) {
    glfwSwapBuffers(app->window);
    glfwPollEvents();
    return glfwWindowShouldClose(app->window);
}

void app_deinit(
    App* app
) {
    glfwDestroyWindow(app->window);
}

bool app_is_key_pressed(Keys key) {

}

Vec2 app_get_mouse_position(
    App *app
) {
    f64 x, y;
    glfwGetCursorPos(app->window, &x, &y);
    LOG(debug, "%f,%f", x, y);

    return (Vec2){(f32)x, (f32)y};
}