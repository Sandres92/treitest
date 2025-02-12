#ifndef FACTORIES_H
#define FACTORIES_H

#include <QString>
#include "objectviewfactory.h"
#include "windowfactory.h"

namespace trei
{
    class Factories
    {
    public:
        Factories();
        ~Factories();

        Window *createWindow(const QXmlStreamReader &xml);
        ObjectView *createObjectView(const QString &className, QXmlStreamReader &xml);

        const QByteArray windowToXML(const Window &window) const;
        const QByteArray objectViewToXML(const ObjectView &window) const;

        void fillXMLAttributeForWindow(const Window &window, QXmlStreamWriter &xml);
        void fillXMLAttributeForObjectView(const ObjectView &objectView, QXmlStreamWriter &xml);
    private:
        WindowFactory windowFactory;
        QMap<QString, ObjectViewFactory *> factories;
    };
}
#endif // FACTORIES_H
