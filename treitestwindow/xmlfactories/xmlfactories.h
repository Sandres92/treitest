#ifndef XMLFACTORIES_H
#define XMLFACTORIES_H

#include<QByteArray>
#include "../window.h"
#include "../objects/objectview.h"
#include "xmlwindowfactory.h"

namespace trei
{
    class XMLFactories
    {
        public:
            XMLFactories();

            const QByteArray windowToXML(const Window &window) const;
            const QByteArray objectViewToXML(const ObjectView &window) const;

            void fillXMLAttributeForWindow(const Window &window, QXmlStreamWriter &xml);
            void fillXMLAttributeForObjectView(const ObjectView &objectView, QXmlStreamWriter &xml);

        private:
            XMLWindowFactory xMLWindowFactory;
    };
}

#endif // XMLFACTORIES_H
