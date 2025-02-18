#include "xmlfactories.h"

#include "xmlobjectviewfactories.h"

namespace trei
{
    XMLFactories::XMLFactories() {}

    //const QByteArray XMLFactories::objectViewToXML(const ObjectView &objectView) const
    //{
    //    QString className = objectView.metaObject()->className();
    //    int doubleColonIndex = className.lastIndexOf("::");
    //
    //    if (doubleColonIndex != -1)
    //    {
    //        className = className.mid(doubleColonIndex + 2);
    //    }
    //
    //    if (!factories.contains(className))
    //    {
    //        return QByteArray();
    //    }
    //
    //    return factories[className]->objectViewToXML(objectView);
    //}

    //const QByteArray XMLFactories::windowToXML(const Window &window) const
    //{
    //    QByteArray additionalByteArray;
    //    const QList<ObjectView *> objectViews = window.getObjectViews();
    //
    //    for (int i = 0; i < objectViews.size(); i++)
    //    {
    //        const QByteArray tempObjectViewArray = objectViewToXML(*objectViews[i]);
    //        additionalByteArray.append(tempObjectViewArray);
    //    }
    //
    //    return xMLWindowFactory.windowToXML(window, additionalByteArray);
    //}

    void XMLFactories::fillXMLAttributeForWindow(const Window &window, QXmlStreamWriter &xml)
    {
        xMLWindowFactory.fillWindowXMLAttribute(window, xml);
    }

    void XMLFactories::fillXMLAttributeForObjectView(const ObjectView &objectView, QXmlStreamWriter &xml)
    {
        XMLObjectViewFactories::instance().fillXMLAttributeForObjectView(objectView, xml);
    }
}
