#include "objectviewfactory2.h"

#include "factories/ellipseviewfactory.h"
#include "factories/rectangleviewfactory.h"
#include "factories/polygonviewfactory.h"

namespace trei
{
    ObjectViewFactory2::ObjectViewFactory2()
    {
        factories["EllipseView"] = new EllipseViewFactory();
        factories["RectangleView"] = new RectangleViewFactory();
        factories["PolygonView"] = new PolygonViewFactory();
    }

    ObjectViewFactory2::~ObjectViewFactory2()
    {
        qDeleteAll(factories);
    }

    ObjectView *ObjectViewFactory2::createObjectView(const QString &className, QXmlStreamReader &xml)
    {
        if (!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView(xml);
    }

    ObjectView *ObjectViewFactory2::createObjectView(const QString &className, float posx, float posy)
    {
        if (!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView(posx, posy);
    }
}
