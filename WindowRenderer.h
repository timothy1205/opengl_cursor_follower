#ifndef OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H
#define OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H

#include "internal.h"

class WindowRenderer {
public:
    virtual void setupOpenGL() const;
    virtual void render() const;
    virtual void setWindowTitle() const;
    virtual WindowSize getVirtualScreenSize();
private:
};


#endif //OPENGL_CURSOR_FOLLOWER_WINDOWRENDERER_H
