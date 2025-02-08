#include "engine.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QString>
#include <QPair>
#include <QDesktopWidget>
#include <QPoint>
#include <QRgb>
#include <QRgba64>
#include <QColor>
#include <QVector>

#include "utility/convector.h"

namespace trei {
    Engine::Engine() {}

    Engine::~Engine() {

    }

    void Engine::init() {
        parseWindow();
    }

    void Engine::parseWindow()
    {
        QFile file(":/resources/figure.xml");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error open file!";
            return;
        }

        QXmlStreamReader xml(&file);
        Window *window = nullptr;
        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartDocument) {
                continue;
            }

            if (token == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "window") {
                    window = createWindow(xml);

                    continue;
                }

                if(xml.name() == "objectView") {
                    QString className = xml.attributes().value("class").toString();

                    if (className == "EllipseView") {
                        EllipseView *ellipseView = createEllipseView(xml);
                        ellipseView->setParent(window);
                    }
                    else if (className == "RectangleView") {
                        RectangleView *rectangleView = createRectangleView(xml);
                        rectangleView->setParent(window);
                    }
                    else if (className == "PolygonView") {
                        PolygonView *polygonView = createPolygonView(xml);
                        polygonView->setParent(window);
                    }
                }
            }
        }

        window->show();
    }

    Window *Engine::createWindow(const QXmlStreamReader &xml) {
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
        //window->show();

        return window;
    }

    RectangleView *Engine::createRectangleView(const QXmlStreamReader &xml) {
        QString name = xml.attributes().value("name").toString();
        float posx = xml.attributes().value("posx").toFloat();
        float posy = xml.attributes().value("posy").toFloat();

        float width = xml.attributes().value("width").toFloat();
        float height = xml.attributes().value("height").toFloat();

        int angle = xml.attributes().value("angle").toInt();
        bool lock = Convector::stringToBool(xml.attributes().value("lock").toString());

        QColor lineColor = Convector::stringHexToColor( xml.attributes().value("color").toString());
        int lineWidth = xml.attributes().value("linewidth").toInt();
        bool fill = Convector::stringToBool(xml.attributes().value("fill").toString());

        QColor fillColor = Convector::stringHexToColor( xml.attributes().value("fillcolor").toString());

        //qDebug() << width << " , " << height;
        RectangleView *rectangleView = new RectangleView(name, posx, posy, width, height, angle,
                                                         lock, lineColor, lineWidth, fill, fillColor);
        return rectangleView;
    }

    EllipseView *Engine::createEllipseView(const QXmlStreamReader &xml) {
        QString name = xml.attributes().value("name").toString();
        float posx = xml.attributes().value("posx").toFloat();
        float posy = xml.attributes().value("posy").toFloat();

        float width = xml.attributes().value("width").toFloat();
        float height = xml.attributes().value("height").toFloat();

        int angle = xml.attributes().value("angle").toInt();
        bool lock = Convector::stringToBool(xml.attributes().value("lock").toString());

        QColor lineColor = Convector::stringHexToColor( xml.attributes().value("color").toString());
        int lineWidth = xml.attributes().value("linewidth").toInt();
        bool fill = Convector::stringToBool(xml.attributes().value("fill").toString());

        QColor fillColor = Convector::stringHexToColor( xml.attributes().value("fillcolor").toString());

        EllipseView *ellipseView = new EllipseView(name, posx, posy, width, height, angle,
                                                         lock, lineColor, lineWidth, fill, fillColor);
        return ellipseView;
    }

    PolygonView *Engine::createPolygonView(QXmlStreamReader &xml) {
        QString name = xml.attributes().value("name").toString();
        float posx = xml.attributes().value("posx").toFloat();
        float posy = xml.attributes().value("posy").toFloat();

        float width = xml.attributes().value("width").toFloat();
        float height = xml.attributes().value("height").toFloat();

        int angle = xml.attributes().value("angle").toInt();
        bool lock = Convector::stringToBool(xml.attributes().value("lock").toString());

        QColor lineColor = Convector::stringHexToColor( xml.attributes().value("color").toString());
        int lineWidth = xml.attributes().value("linewidth").toInt();
        bool fill = Convector::stringToBool(xml.attributes().value("fill").toString());

        QColor fillColor = Convector::stringHexToColor( xml.attributes().value("fillcolor").toString());

        PolygonView *polygonView = new PolygonView(name, posx, posy, width, height, angle,
                                                   lock, lineColor, lineWidth, fill, fillColor);

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
