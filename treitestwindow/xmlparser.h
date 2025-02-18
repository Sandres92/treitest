#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QString>
#include "objectfactories/factories.h"
#include "xmlfactories/xmlfactories.h"

namespace trei
{
    class XMLParser : public QObject
    {
        Q_OBJECT

    public:
        XMLParser(QObject *parent = nullptr);
        ~XMLParser() = default;

        QList<Window *> load();
        void save(QList<Window *> windows);

    signals:
        void xmlLoaded(QList<Window *> windows);

    private:
        Factories factories;
        trei::XMLFactories XMLFactories;
    };
}
#endif // XMLPARSER_H
