#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <csignal>

void getVirtualDesktopDimensions(int* width, int* height);

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

    /*
     * Window managers need to disable managing for window
     * Ex: bspc rule -a opengl_cursor_follower manage=off
     */

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);

    // Create window based on virtual desktop dimensions
    int width, height;
    getVirtualDesktopDimensions(&width, &height);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "opengl_cursor_follower", glfwGetPrimaryMonitor(), NULL);
    glfwSetWindowPos(window, -500, 100);
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 0, 0);

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

void getVirtualDesktopDimensions(int* width, int* height) {
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    if (!monitors) {
        std::cerr << "No monitors found..." << std::endl;
        exit(EXIT_FAILURE);
    }

    *width = 0;
    *height = 0;

    int xPos, yPos, tWidth, tHeight;
    for (int i = 0; i < monitorCount; i++) {
        glfwGetMonitorWorkarea(monitors[i], &xPos, &yPos, &tWidth, &tHeight);

        int right = xPos + tWidth;
        if (right > *width) {
            *width = right;
        }
        int bottom = yPos + tHeight;
        if (bottom > *height) {
            *height = bottom;
        }
    }
}