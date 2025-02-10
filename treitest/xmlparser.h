#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QString>
#include "factories/objectviewfactories.h"

namespace trei {
    class XMLParser
    {
        public:
            XMLParser() = default;
            ~XMLParser() = default;

            QList<Window*> load();
            void save(QList<Window*>) const;

        private:
            ObjectViewFactories objectViewFactories;
    };
}
#endif // XMLPARSER_H
