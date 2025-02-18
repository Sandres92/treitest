#include "objectviewfactories.h"

#include "ellipseviewfactory.h"
#include "rectangleviewfactory.h"
#include "polygonviewfactory.h"

namespace trei
{
    ObjectViewFactories::ObjectViewFactories()
    {
        factories["EllipseView"] = new EllipseViewFactory();
        factories["RectangleView"] = new RectangleViewFactory();
        factories["PolygonView"] = new PolygonViewFactory();
    }

    ObjectViewFactories::~ObjectViewFactories()
    {
        qDeleteAll(factories);
    }

    bool ObjectViewFactories::isContainsFactory(const QString &className)
    {
        return factories.contains(className);
    }

    ObjectView *ObjectViewFactories::createObjectView(const QString &className)
    {
        if (!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView();
    }

    ObjectView *ObjectViewFactories::createObjectView(const QString &className, QXmlStreamReader &xml)
    {
        if (!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView(xml);
    }

    ObjectView *ObjectViewFactories::createObjectView(const QString &className, float posx, float posy)
    {
        if (!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView(posx, posy);
    }
}
