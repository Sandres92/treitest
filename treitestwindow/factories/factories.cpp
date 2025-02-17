#include "factories.h"

#include "factories/ellipseviewfactory.h"
#include "factories/rectangleviewfactory.h"
#include "factories/polygonviewfactory.h"

namespace trei
{
    Factories::Factories()
    {
        factories["EllipseView"] = new EllipseViewFactory();
        factories["RectangleView"] = new RectangleViewFactory();
        factories["PolygonView"] = new PolygonViewFactory();
    }

    Factories::~Factories()
    {
        qDeleteAll(factories);
        factories.clear();
    }

    ObjectView *Factories::createObjectView(const QString &className, QXmlStreamReader &xml)
    {
        if (!factories.contains(className))
        {
            return nullptr;
        }

        return factories[className]->createObjectView(xml);
    }

    const QByteArray Factories::objectViewToXML(const ObjectView &objectView) const
    {
        QString className = objectView.metaObject()->className();
        int doubleColonIndex = className.lastIndexOf("::");

        if (doubleColonIndex != -1)
        {
            className = className.mid(doubleColonIndex + 2);
        }

        if (!factories.contains(className))
        {
            return QByteArray();
        }

        return factories[className]->objectViewToXML(objectView);
    }

    Window *Factories::createWindow(const QXmlStreamReader &xml)
    {

        return windowFactory.createWindow(xml);
    }

    const QByteArray Factories::windowToXML(const Window &window) const
    {
        QByteArray additionalByteArray;
        const QList<ObjectView *> objectViews = window.getObjectViews();

        for (int i = 0; i < objectViews.size(); i++)
        {
            const QByteArray tempObjectViewArray = objectViewToXML(*objectViews[i]);
            additionalByteArray.append(tempObjectViewArray);
        }

        return windowFactory.windowToXML(window, additionalByteArray);
    }

    void Factories::fillXMLAttributeForWindow(const Window &window, QXmlStreamWriter &xml)
    {
        windowFactory.fillWindowXMLAttribute(window, xml);
    }

    void Factories::fillXMLAttributeForObjectView(const ObjectView &objectView, QXmlStreamWriter &xml)
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
