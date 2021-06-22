#ifndef OPENGL_CURSOR_FOLLOWER_X11_WINDOWRENDERER_H
#define OPENGL_CURSOR_FOLLOWER_X11_WINDOWRENDERER_H

#include <X11/Xlib.h>
#include "opengl.h"
#include "WindowRenderer.h"

class x11_WindowRenderer: virtual public WindowRenderer {
public:
    x11_WindowRenderer();
    x11_WindowRenderer(bool debugBackground);
    ~x11_WindowRenderer();

    void render() const override;
    void setWindowTitle() const override;
    WindowSize getVirtualScreenSize() override;

private:
    Display* display;
    Window window;
    GLXContext context;
};


#endif //OPENGL_CURSOR_FOLLOWER_X11_WINDOWRENDERER_H
