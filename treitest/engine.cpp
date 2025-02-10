#include "engine.h"

namespace trei {
    Engine::Engine()
    {

    }

    Engine::~Engine() {

    }

    void Engine::init() {
        loadXML();
        saveXML();
    }

    void Engine::loadXML()
    {
        xMLParser.load();
    }

    void Engine::saveXML()
    {
        //xMLParser.save();
    }
}
