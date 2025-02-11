#include "engine.h"

namespace trei {
    Engine::Engine()
    {
        //keyCtrlS = new QShortcut(this);
        //keyCtrlS->setKey(Qt::CTRL + Qt::Key_S);
        //connect(keyCtrlS, SIGNAL(activated()), this, SLOT(slotShortcutCtrlS()));
    }

    Engine::~Engine()
    {
        qDeleteAll(windows);
    }

    void Engine::init() {
        loadXML();
    }

    void Engine::loadXML()
    {
        windows = xMLParser.load();
    }

    void Engine::saveXML()
    {
        xMLParser.save(windows);
    }

    void Engine::slotShortcutCtrlS()
    {

    }
}
