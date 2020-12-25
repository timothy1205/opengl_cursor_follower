#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <csignal>
#include "WindowRendererManager.h"

namespace {
    bool interrupted = false;
}

int main() {
    // Handle program interruption
    std::signal(SIGINT, [](int) { interrupted = true; });

    glfwInit();

    /*
     * Version 3.4 is necessary for GLFW_MOUSE_PASSTHROUGH, however specifying it
     * as such causes the window to not be created...
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Global window hints
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);

    WindowRendererManager windowRendererManager;

    // Main application loop
    while (!interrupted) {
        #ifdef DEBUG_AUTO_CLOSE
        if (glfwGetTime() > 5) {
            std::cout << "Debug: Auto closing..." << std::endl;
            break;
        }
        #endif
    }

    glfwTerminate();
    return 0;
}