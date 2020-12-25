#include "WindowRenderer.h"
#include <iostream>

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
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
}

WindowRenderer::~WindowRenderer() = default;

void WindowRenderer::render() {
    if (!shouldRender()) return;

    glfwMakeContextCurrent(window);
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawSprite();

    glfwSwapBuffers(window);
}

bool WindowRenderer::shouldRender() {
    // TODO: Check if sprite is on window
    return true;
}

void WindowRenderer::drawSprite() {
    // TODO: Tell opengl to render stored sprite
}
