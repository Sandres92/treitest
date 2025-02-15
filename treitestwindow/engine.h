#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>
#include <QWidget>
#include <QShortcut>
#include "xmlparser.h"

namespace trei {
    class Engine
    {
        public:
            Engine();
            ~Engine();

            void init();

        private slots:
            void slotShortcutCtrlS();

        private:
            void loadXML();
            void saveXML();

            XMLParser xMLParser;
            QList<Window*> windows;

            QShortcut *keyCtrlS;
    };
}


#endif // ENGINE_H
