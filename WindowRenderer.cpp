#include "WindowRenderer.h"
#include "opengl.h"
#include "internal.h"

WindowRenderer::WindowRenderer() = default;

WindowRenderer::WindowRenderer(bool debugBackground) {
    this->debugBackground = debugBackground;
}

void WindowRenderer::setupOpenGL() const {
    if (this->debugBackground) {
        glClearColor(0.1, 0.0, 0.0, 0.1);
    } else {
        glClearColor(0.0, 0.0, 0.0, 0.0);
    }
}

void WindowRenderer::render() const {}

void WindowRenderer::setWindowTitle() const {}

WindowSize WindowRenderer::getVirtualScreenSize() {
    return WindowSize();
}
