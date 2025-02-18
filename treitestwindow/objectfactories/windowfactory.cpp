#include "windowfactory.h"

#include "../utility/convector.h"

namespace trei
{
    Window *WindowFactory::createWindow(const QXmlStreamReader &xml)
    {
        auto isOutOfDesktop = [](const QWidget & w)
        {
            QDesktopWidget *desktopWidget = QApplication::desktop();
            const QRect screenRect = desktopWidget->screenGeometry(&w);
            const QPoint topLeft = w.mapToGlobal(w.geometry().topLeft());
            const QPoint bottomRight = w.mapToGlobal(w.geometry().bottomRight());

            if (!screenRect.contains(topLeft) || !screenRect.contains(bottomRight))
            {
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

        Window *window = new Window(name, color, type, windowWidth, windowHeight, usePassword,
                                    password, groupName, subGroupName, posx, posy, accessLevel);

        if (isOutOfDesktop(*window))
        {
            window->move(0, 0);
        }

        return window;
    }

    Window *WindowFactory::createWindow(int countWindows)
    {
        Window *newWindow = new Window("Экран" + QString::number(countWindows));
        newWindow->show();

        return newWindow;
    }
}
