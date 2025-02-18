#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QString>
#include "objectfactories/factories.h"
#include "xmlfactories/xmlfactories.h"

namespace trei
{
    class XMLParser
    {
    public:
        XMLParser() = default;
        ~XMLParser() = default;

        QList<Window *> load();
        void save(QList<Window *> windows);

    private:
        Factories factories;
        XMLFactories XMLFactories;
    };
}
#endif // XMLPARSER_H
