#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "window.h"

namespace trei
{
    class WindowFactory
    {
    public:
        WindowFactory() = default;
        ~WindowFactory() = default;

        Window *createWindow(const QXmlStreamReader &xml);
        const QByteArray windowToXML(const Window &window, const QByteArray &additionalByteArray) const;
        void fillWindowXMLAttribute(const Window &window, QXmlStreamWriter &xml);

    private:

    };
}
#endif // WINDOWFACTORY_H
