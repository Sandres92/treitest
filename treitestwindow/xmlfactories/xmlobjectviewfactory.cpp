#include "xmlobjectviewfactory.h"

#include "utility/convector.h"

namespace trei
{
    const QByteArray XMLObjectViewFactory::objectViewToXML(const ObjectView &objectView) const
    {
        QByteArray buffer;
        QXmlStreamWriter xml(&buffer);
        xml.setAutoFormatting(true);

        xml.writeStartElement("objectView");
        xml.writeAttribute("class", objectView.metaObject()->className());
        xml.writeAttribute("name", objectView.getName());
        xml.writeAttribute("posx", QString::number(objectView.getPosx()));
        xml.writeAttribute("posy", QString::number(objectView.getPosy()));
        xml.writeAttribute("width", QString::number(objectView.getWidth()));
        xml.writeAttribute("height", QString::number(objectView.getHeight()));
        xml.writeAttribute("angle", QString::number(objectView.getAngle()));
        xml.writeAttribute("lock", Convector::boolToString(objectView.getLock()));
        xml.writeAttribute("color", Convector::colorToHexColorString(objectView.getLineColor()));
        xml.writeAttribute("linewidth", QString::number(objectView.getLineWidth()));
        xml.writeAttribute("fill", Convector::boolToString(objectView.getFill()));
        xml.writeAttribute("fillcolor", Convector::colorToHexColorString(objectView.getFillColor()));

        xml.writeStartElement("scripts");
        xml.writeEndElement();

        addAdditionalXMLElements(objectView, xml);

        xml.writeEndElement();
        return buffer;
    }

    void XMLObjectViewFactory::fillXMLAttributeForObjectView(const ObjectView &objectView, QXmlStreamWriter &xml)
    {
        QString className = Convector::fullCalssNameToShort(objectView.metaObject()->className());
        xml.writeAttribute("class", className);
        xml.writeAttribute("name", objectView.getName());
        xml.writeAttribute("posx", QString::number(objectView.getPosx()));
        xml.writeAttribute("posy", QString::number(objectView.getPosy()));
        xml.writeAttribute("width", QString::number(objectView.getWidth()));
        xml.writeAttribute("height", QString::number(objectView.getHeight()));
        xml.writeAttribute("angle", QString::number(objectView.getAngle()));
        xml.writeAttribute("lock", Convector::boolToString(objectView.getLock()));
        xml.writeAttribute("color", Convector::colorToHexColorString(objectView.getLineColor()));
        xml.writeAttribute("linewidth", QString::number(objectView.getLineWidth()));
        xml.writeAttribute("fill", Convector::boolToString(objectView.getFill()));
        xml.writeAttribute("fillcolor", Convector::colorToHexColorString(objectView.getFillColor()));

        xml.writeStartElement("scripts");
        xml.writeEndElement();

        addAdditionalXMLElements(objectView, xml);
    }

    void XMLObjectViewFactory::addAdditionalXMLElements(const ObjectView &objectView, QXmlStreamWriter &xml) const {}
}
