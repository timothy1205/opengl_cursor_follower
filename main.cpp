#include <csignal>
#include <iostream>
#include <unistd.h>

#include <argparser.hpp>

#include "config.h"
#ifdef USE_X11
#include "x11_WindowRenderer.h"
#endif
namespace {
    bool showHelp = false;
    bool debugBackground = false;

    bool interrupted = false;
}

int main(int argc, char const* argv[]) {
    stypox::ArgParser parser{std::make_tuple(
        stypox::HelpSection{"\nOptions:"},

        stypox::SwitchOption{"help", showHelp, stypox::args("-h", "--help"),  "Print help"},
        stypox::SwitchOption{"debugbg", debugBackground, stypox::args("--debug-background"),  "Show colored background for debugging"}
    ), "OpenGL Cursor Follower"};

    parser.parse(argc, argv);

    if (showHelp) {
        std::cout << parser.help();
        return EXIT_SUCCESS;
    }

    // Handle program interruption
    std::signal(SIGINT, [](int) { interrupted = true; });

#ifdef USE_X11
    x11_WindowRenderer windowRenderer{debugBackground};
#endif

    while (!interrupted) {
        windowRenderer.render();
        usleep((1/60) * 1000000);
    }
}
