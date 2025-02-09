#include "engine.h"

namespace trei {
    Engine::Engine() {}

    Engine::~Engine() {

    }

    void Engine::init() {
        parseWindow();
    }

    void Engine::parseWindow()
    {
        xMLParser.load();
    }
}
