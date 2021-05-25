#include <iostream>
#include <cstdlib>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/shape.h>
#include "x11_WindowRenderer.h"
#include "internal.h"

x11_WindowRenderer::x11_WindowRenderer() {
    display = XOpenDisplay(nullptr);

    if (!display) {
        std::cerr << "Failed to create connection to x11 server\n";
        exit(EXIT_FAILURE);
    }

    // Query for visual info
    XVisualInfo visualInfo;
    XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &visualInfo);

    XSetWindowAttributes attributes;
    attributes.colormap = XCreateColormap(display, DefaultRootWindow(display), visualInfo.visual, AllocNone);
    attributes.event_mask = NoEventMask;
    attributes.background_pixmap = None;
    attributes.border_pixel = 0;
    // Allow for input passthrough
    attributes.override_redirect = True;

    WindowSize size = x11_WindowRenderer::getVirtualScreenSize();

    window = XCreateWindow(display, DefaultRootWindow(display),
                           // x, y, width, height
                           0, 0, size.width, size.height,
                           0, visualInfo.depth, InputOutput, visualInfo.visual,
                           CWBackPixel | CWColormap | CWBorderPixel | CWEventMask | CWOverrideRedirect,
                           &attributes);

    GC gc = XCreateGC(display, window, 0, nullptr);

    this->setWindowTitle();

    XGCValues gcValues;
    XChangeGC(display, gc, GCForeground, &gcValues);

    context = glXCreateContext(display, &visualInfo, nullptr, True);
    if (!context) {
        std::cerr << "Failed to create opengl context!\n";
        exit(EXIT_FAILURE);
    }
    glXMakeCurrent(display, window, context);

    XMapWindow(display, window);

    // Allow input passthrough
    XserverRegion region = XFixesCreateRegion (display, NULL, 0);
    XFixesSetWindowShapeRegion(display, window, ShapeBounding, 0, 0, 0);
    XFixesSetWindowShapeRegion(display, window, ShapeInput, 0, 0, region);
    XFixesDestroyRegion(display, region);

    WindowRenderer::setupOpenGL();
}

x11_WindowRenderer::~x11_WindowRenderer() = default;

void x11_WindowRenderer::render() const {
    glClear(GL_COLOR_BUFFER_BIT);
    glXSwapBuffers(display, window);
}

void x11_WindowRenderer::setWindowTitle() const {
    XStoreName(display, window, WINDOW_TITLE) ;
}

WindowSize x11_WindowRenderer::getVirtualScreenSize() {
    Screen* screen = ScreenOfDisplay(display, DefaultScreen(display));
    WindowSize size;
    size.width = XWidthOfScreen(screen);
    size.height = XHeightOfScreen(screen);

    return size;
}
