#ifndef XMLWINDOWFACTORY_H
#define XMLWINDOWFACTORY_H

#include "QByteArray"

#include "../window.h"

namespace trei
{
    class XMLWindowFactory
    {
    public:
        XMLWindowFactory() = default;
        ~XMLWindowFactory() = default;

        const QByteArray windowToXML(const Window &window, const QByteArray &additionalByteArray) const;
        void fillWindowXMLAttribute(const Window &window, QXmlStreamWriter &xml);
    };
}
#endif // XMLWINDOWFACTORY_H
