#include "xmlpolygonviewfactory.h"

#include "objects/polygonview.h"

namespace trei
{
    XMLPolygonViewFactory::XMLPolygonViewFactory() {}

    void XMLPolygonViewFactory::addAdditionalXMLElements(const ObjectView &objectView, QXmlStreamWriter &xml) const
    {
        const PolygonView *polygonView = dynamic_cast<const PolygonView *>(&objectView);
        //const PolygonView &polygonView2 = dynamic_cast<const PolygonView &>(objectView);

        if (polygonView)
        {
            xml.writeStartElement("coordinates");
            QVector<QPointF> coords = polygonView->getCoords();

            for (int i = 0; i < coords.size(); i++)
            {
                xml.writeStartElement("coordinate");
                xml.writeAttribute("coordx", QString::number(coords[i].x()));
                xml.writeAttribute("coordy", QString::number(coords[i].y()));
                xml.writeEndElement();
            }

            xml.writeEndElement();
        }
    }
}
