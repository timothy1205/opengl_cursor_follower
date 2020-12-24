#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <csignal>
#include <X11/Xlib.h>

void getVirtualDesktopDimensions(int* width, int* height);

namespace {
    bool interrupted = false;
}

int main() {
    // Handle program interruption
    std::signal(SIGINT, [](int) { interrupted = true; });

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    // Create window based on virtual desktop dimensions
    int width, height;
    getVirtualDesktopDimensions(&width, &height);
    GLFWwindow* window = glfwCreateWindow(width, height, "opengl_cursor_follower", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 0, 0);

    // Main application loop
    while (!interrupted) {

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