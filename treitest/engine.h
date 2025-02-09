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
            XMLParser xMLParser;

            void loadXML();
            void saveXML();
    };
}


#endif // ENGINE_H
