#include "xmlobjectviewfactories.h"

#include "xmlellipseviewfactory.h"
#include "xmlrectangleviewfactory.h"
#include "xmlpolygonviewfactory.h"

namespace trei
{
    XMLObjectViewFactories::XMLObjectViewFactories()
    {
        factories["EllipseView"] = new XMLEllipseViewFactory();
        factories["RectangleView"] = new XMLRectangleViewFactory();
        factories["PolygonView"] = new XMLPolygonViewFactory();
    }

    bool XMLObjectViewFactories::isContainsFactory(const QString &className)
    {
        return factories.contains(className);
    }

    void XMLObjectViewFactories::fillXMLAttributeForObjectView(const ObjectView &objectView, QXmlStreamWriter &xml)
    {
        QString className = objectView.metaObject()->className();
        int doubleColonIndex = className.lastIndexOf("::");

        if (doubleColonIndex != -1)
        {
            className = className.mid(doubleColonIndex + 2);
        }

        if (factories.contains(className))
        {
            factories[className]->fillXMLAttributeForObjectView(objectView, xml);
        }
    }
}
