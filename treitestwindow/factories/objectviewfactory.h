#ifndef OBJECTVIEWFACTORY_H
#define OBJECTVIEWFACTORY_H

#include <QXmlStreamReader>
#include <QXmlStreamAttributes>

#include "objects/objectview.h"
#include "utility/convector.h"

namespace trei
{
    class ObjectViewFactory
    {
    public:
        explicit ObjectViewFactory() = default;
        virtual ~ObjectViewFactory() = default;

        virtual ObjectView *createObjectView(QXmlStreamReader &xml) = 0;
        const QByteArray objectViewToXML(const ObjectView &objectView) const;

    protected:
        template <typename T>
        T *createCommonObjectView(const QXmlStreamReader &xml) {
            static_assert(std::is_base_of<ObjectView, T>::value, "T must be a descendant of ObjectView");

            QString name = xml.attributes().value("name").toString();
            float posx = xml.attributes().value("posx").toFloat();
            float posy = xml.attributes().value("posy").toFloat();

            float width = xml.attributes().value("width").toFloat();
            float height = xml.attributes().value("height").toFloat();

            int angle = xml.attributes().value("angle").toInt();
            bool lock = Convector::stringToBool(xml.attributes().value("lock").toString());

            QColor lineColor = Convector::stringHexToColor(xml.attributes().value("color").toString());
            int lineWidth = xml.attributes().value("linewidth").toInt();
            bool fill = Convector::stringToBool(xml.attributes().value("fill").toString());

            QColor fillColor = Convector::stringHexToColor(xml.attributes().value("fillcolor").toString());

            return new T(name, posx, posy, width, height, angle,
                         lock, lineColor, lineWidth, fill, fillColor);
        }

        virtual void addAdditionalXMLElements(const ObjectView &objectView, QXmlStreamWriter &xml) const;
    };
}
#endif // OBJECTVIEWFACTORY_H
