#include "polygonviewfactory.h"

#include "objects/polygonview.h"
#include <QVector>
#include <QPointF>

namespace trei
{
    ObjectView *PolygonViewFactory::createObjectView(QXmlStreamReader &xml)
    {
        PolygonView *polygonView = createCommonObjectView<PolygonView>(xml);

        QVector<QPointF> coords;

        while (!(xml.name() == "objectView" && xml.tokenType() == QXmlStreamReader::EndElement))
        {
            //if(xml.tokenType() == QXmlStreamReader::StartElement)
            //{
            //    qDebug() << " start " << " , " << xml.name();
            //}
            //else if(xml.tokenType() == QXmlStreamReader::EndElement)
            //{
            //    qDebug() << " end " << " , " << xml.name();
            //}
            xml.readNext();

            if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "coordinate")
            {
                float coordx = xml.attributes().value("coordx").toFloat();
                float coordy = xml.attributes().value("coordy").toFloat();
                coords.append(QPointF(coordx, coordy));
            }
        }

        polygonView->setCoords(coords);

        return polygonView;
    }

    void PolygonViewFactory::addAdditionalXMLElements(const ObjectView &objectView, QXmlStreamWriter &xml) const
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
