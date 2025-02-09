#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>

#include <QWidget>

#include "xmlparser.h"

namespace trei {
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void init();

    private:
        void parseWindow();

        XMLParser xMLParser;
    };
}


#endif // ENGINE_H
