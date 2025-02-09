#include "polygonviewfactory.h"

#include "objects/polygonview.h"
#include <QVector>
#include <QPointF>

namespace trei
{
    ObjectView* PolygonViewFactory::createObjectView(QXmlStreamReader &xml)
    {
        PolygonView *polygonView = createCommonObjectView<PolygonView>(xml);

        QVector<QPointF> coords;
        while (!(xml.name() == "objectView" && xml.tokenType() == QXmlStreamReader::EndElement)) {
            //if(xml.tokenType() == QXmlStreamReader::StartElement)
            //{
            //    qDebug() << " start " << " , " << xml.name();
            //}
            //else if(xml.tokenType() == QXmlStreamReader::EndElement)
            //{
            //    qDebug() << " end " << " , " << xml.name();
            //}
            xml.readNext();

            if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "coordinate") {
                float coordx = xml.attributes().value("coordx").toFloat();
                float coordy = xml.attributes().value("coordy").toFloat();
                coords.append(QPointF(coordx, coordy));
            }
        }
        polygonView->setCoords(coords);

        return polygonView;
    }
}
