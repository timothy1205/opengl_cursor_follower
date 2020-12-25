#ifndef OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H
#define OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class WindowRenderer {
public:
    explicit WindowRenderer(GLFWmonitor* monitor);
    ~WindowRenderer();

    void render() const;

private:
    GLFWwindow* window;

    bool shouldRender() const;
    void drawSprite() const;

};


#endif //OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H
