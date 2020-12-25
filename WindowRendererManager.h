#ifndef OPENGL_CURSOR_FOLLOWER_WINDOWRENDERERMANAGER_H
#define OPENGL_CURSOR_FOLLOWER_WINDOWRENDERERMANAGER_H

#include <vector>
#include "WindowRenderer.h"

class WindowRendererManager {
public:
    WindowRendererManager();
    ~WindowRendererManager();

    void triggerRenderers();
private:
    std::vector<WindowRenderer> renders;
};


#endif //OPENGL_CURSOR_FOLLOWER_WINDOWRENDERERMANAGER_H
