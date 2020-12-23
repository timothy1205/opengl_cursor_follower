#ifndef OPENGL_CURSOR_FOLLOWER_RENDERER_H
#define OPENGL_CURSOR_FOLLOWER_RENDERER_H

#include <glm/glm.hpp>

typedef struct Follower_Struct {
    glm::vec2 position;
} Follower;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void setFollowerPosition(float x, float y);
    void drawFollower();

private:
    GLFWwindow* window;

};


#endif //OPENGL_CURSOR_FOLLOWER_RENDERER_H
