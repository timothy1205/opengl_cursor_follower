#ifndef OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H
#define OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class WindowRenderer {
public:
    explicit WindowRenderer(GLFWmonitor* monitor);
    ~WindowRenderer();

private:
    GLFWwindow* window;

};


#endif //OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H
