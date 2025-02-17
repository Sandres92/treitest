#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QString>
#include "objectfactories/factories.h"

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
    };
}
#endif // XMLPARSER_H
