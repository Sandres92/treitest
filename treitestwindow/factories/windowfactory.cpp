#include "windowfactory.h"

#include "../utility/convector.h"

namespace trei
{
    Window *WindowFactory::createWindow(const QXmlStreamReader &xml)
    {
        auto isOutOfDesktop = [](const QWidget &w) {
            QDesktopWidget *desktopWidget = QApplication::desktop();
            const QRect screenRect = desktopWidget->screenGeometry(&w);
            const QPoint topLeft = w.mapToGlobal(w.geometry().topLeft());
            const QPoint bottomRight = w.mapToGlobal(w.geometry().bottomRight());

            if(!screenRect.contains(topLeft) || !screenRect.contains(bottomRight)){
                return true;
            }

            return false;
        };

        const QString name = xml.attributes().value("name").toString();
        const QColor color = Convector::stringHexToColor(xml.attributes().value("color").toString());
        const int type = xml.attributes().value("type").toInt();

        const int windowHeight = xml.attributes().value("windowheight").toInt();
        const int windowWidth = xml.attributes().value("windowwidth").toInt();

        const bool usePassword = Convector::stringToBool(xml.attributes().value("usepassword").toString());
        const QString password = xml.attributes().value("password").toString();

        const QString groupName = xml.attributes().value("groupname").toString();
        const QString subGroupName = xml.attributes().value("subgroupname").toString();

        const int posx = xml.attributes().value("posx").toInt();
        const int posy = xml.attributes().value("posy").toInt();

        const int accessLevel = xml.attributes().value("accesslevel").toInt();

        Window *window = new Window(name, color, type, windowWidth, windowHeight, windowWidth,
                                    password, groupName, subGroupName, posx, posy, accessLevel);

        if(isOutOfDesktop(*window))
        {
            window->move(0, 0);
        }

        return window;
    }

    const QByteArray WindowFactory::windowToXML(const Window &window) const
    {
        QByteArray buffer;
        QXmlStreamWriter xml(&buffer);

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

        xml.writeEndElement();

        return buffer;
    }
}
