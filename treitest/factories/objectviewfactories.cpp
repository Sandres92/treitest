#include "objectviewfactories.h"

#include "factories/ellipseviewfactory.h"
#include "factories/rectangleviewfactory.h"
#include "factories/polygonviewfactory.h"

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
        factories.clear();
    }

    Window *ObjectViewFactories::createWindow(const QXmlStreamReader &xml)
    {
        return windowFactory.createWindow(xml);
    }

    ObjectView *ObjectViewFactories::createObjectView(const QString &className, QXmlStreamReader &xml)
    {
        if(!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView(xml);
    }
}
