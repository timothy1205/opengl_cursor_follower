#include <iostream>
#include <csignal>
#ifdef _USE_X11
#include "x11_WindowRenderer.h"
#endif

namespace {
    bool interrupted = false;
}

int main(int argc, char** argv) {
    // Handle program interruption
    std::signal(SIGINT, [](int) { interrupted = true; });

#ifdef _USE_X11
    x11_WindowRenderer windowRenderer;
#endif

    while (!interrupted) {
        windowRenderer.render();
    }

}