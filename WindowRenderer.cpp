#include "WindowRenderer.h"


WindowRenderer::WindowRenderer(GLFWmonitor* monitor) {
    /*
    * Window managers need to disable managing for window
    * Ex: 'bspc rule -a opengl_cursor_follower manage=off'
    */

    // Create a windowed-fullscreen window
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(mode->width, mode->height, "opengl_cursor_follower", monitor, nullptr);
}

WindowRenderer::~WindowRenderer() = default;
