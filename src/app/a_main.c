//
// Created by Cory Smith on 7/25/25.
//

#include "app.h"
#include <GLFW/glfw3.h>


typedef struct Mouse {
} Mouse;

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

    app->window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);
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

void app_is_key_pressed(Keys key) {

}