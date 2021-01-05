#include "WindowRenderer.h"
#include "opengl.h"
#include "internal.h"

void WindowRenderer::setupOpenGL() const {
    glClearColor(0.7, 0.0, 0.0, 0.7);
}

void WindowRenderer::render() const {
}

void WindowRenderer::setWindowTitle() const {}

WindowSize WindowRenderer::getVirtualScreenSize() {
    return WindowSize();
}
