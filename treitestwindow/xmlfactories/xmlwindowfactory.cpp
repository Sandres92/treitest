#include "xmlwindowfactory.h"

namespace trei
{
    const QByteArray XMLWindowFactory::windowToXML(const Window &window, const QByteArray &additionalByteArray) const
    {
        QByteArray buffer;
        QXmlStreamWriter xml(&buffer);
        xml.setAutoFormatting(true);

        xml.writeStartElement("window");

        xml.writeAttribute("name", window.getName());
        xml.writeAttribute("color", Convector::colorToHexColorString(window.getColor()));
        xml.writeAttribute("type", QString::number(window.getType()));
        xml.writeAttribute("windowheight", QString::number(window.getWindowHeight()));
        xml.writeAttribute("windowwidth", QString::number(window.getWindowWidth()));
        xml.writeAttribute("usepassword", Convector::boolToString(window.getUsePassword()));
        xml.writeAttribute("password", window.getPassword());
        xml.writeAttribute("groupname", window.getGroupName());
        xml.writeAttribute("subgroupname", window.getSubGroupName());
        xml.writeAttribute("posx", QString::number(window.getPosx()));
        xml.writeAttribute("posy", QString::number(window.getPosy()));
        xml.writeAttribute("accesslevel", QString::number(window.getAccessLevel()));

        xml.writeStartElement("scripts");
        xml.writeEndElement();

        buffer.append(additionalByteArray);

        xml.writeEndElement();

        return buffer;
    }

    void XMLWindowFactory::fillWindowXMLAttribute(const Window &window, QXmlStreamWriter &xml)
    {
        xml.writeAttribute("name", window.getName());
        xml.writeAttribute("color", Convector::colorToHexColorString(window.getColor()));
        xml.writeAttribute("type", QString::number(window.getType()));
        xml.writeAttribute("windowheight", QString::number(window.getWindowHeight()));
        xml.writeAttribute("windowwidth", QString::number(window.getWindowWidth()));
        xml.writeAttribute("usepassword", Convector::boolToString(window.getUsePassword()));
        xml.writeAttribute("password", window.getPassword());
        xml.writeAttribute("groupname", window.getGroupName());
        xml.writeAttribute("subgroupname", window.getSubGroupName());
        xml.writeAttribute("posx", QString::number(window.getPosx()));
        xml.writeAttribute("posy", QString::number(window.getPosy()));
        xml.writeAttribute("accesslevel", QString::number(window.getAccessLevel()));
    }
}
