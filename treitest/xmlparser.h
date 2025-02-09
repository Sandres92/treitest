#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QString>
#include "factories/objectviewfactories.h"

namespace trei {
    class XMLParser
    {
        public:
            XMLParser();
            ~XMLParser();

            void load();
            void save();

        private:
            ObjectViewFactories objectViewFactories;
    };
}
#endif // XMLPARSER_H
