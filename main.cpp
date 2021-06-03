#include <iostream>
#include <csignal>
#include <unistd.h>
#include "config.h"
#ifdef USE_X11
#include "x11_WindowRenderer.h"
#endif

namespace {
    bool interrupted = false;
}

int main(int argc, char** argv) {
    // Handle program interruption
    std::signal(SIGINT, [](int) { interrupted = true; });

#ifdef USE_X11
    x11_WindowRenderer windowRenderer;
#endif

    while (!interrupted) {
        windowRenderer.render();
        usleep((1/60) * 1000000);
    }

}
