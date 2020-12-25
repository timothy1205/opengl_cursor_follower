#include "WindowRendererManager.h"
#include "WindowRenderer.h"
WindowRendererManager::WindowRendererManager() {
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++) {
        renders.emplace_back(WindowRenderer(monitors[i]));
    }
}

void WindowRendererManager::triggerRenderers() {
    for (auto render: renders) {
        render.render();
    }
}

WindowRendererManager::~WindowRendererManager() = default;
