#include "windowfactory.h"

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

        QString name = xml.attributes().value("name").toString();
        QString color = xml.attributes().value("color").toString().remove(0,2);
        int type = xml.attributes().value("type").toInt();

        int windowwidth = xml.attributes().value("windowwidth").toInt();
        int windowheight = xml.attributes().value("windowheight").toInt();

        int posx = xml.attributes().value("posx").toInt();
        int posy = xml.attributes().value("posy").toInt();

        Window *window = new Window();
        window->resize(windowwidth, windowheight);
        window->setWindowTitle(name);
        window->move(posx, posy);
        if(isOutOfDesktop(*window))
        {
            window->move(0, 0);
        }
        window->setStyleSheet("background-color:#" + color + ";");

        return window;
    }

    const QByteArray WindowFactory::windowToXML(const Window &window) const
    {
        QByteArray buffer;
        QXmlStreamWriter xml(&buffer);

        xml.writeStartElement("window");
        xml.writeAttribute("name", window.getName());
        //xml.writeAttribute("name", window.getName());

        xml.writeEndElement();

        return buffer;
    }
}
