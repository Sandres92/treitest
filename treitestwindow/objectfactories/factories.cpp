#include "factories.h"

namespace trei
{
    ObjectView *Factories::createObjectView(const QString &className, QXmlStreamReader &xml)
    {
        return ObjectViewFactories::instance().createObjectView(className, xml);
    }

    Window *Factories::createWindow(const QXmlStreamReader &xml)
    {
        return windowFactory.createWindow(xml);
    }
}
