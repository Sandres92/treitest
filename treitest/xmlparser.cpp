#include "xmlparser.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

namespace trei {
    XMLParser::XMLParser()
    {
    }

    XMLParser::~XMLParser()
    {
    }

    void XMLParser::load()
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
                    window = objectViewFactories.createWindow(xml);

                    continue;
                }

                if(xml.name() == "objectView") {
                    QString className = xml.attributes().value("class").toString();
                    ObjectView *objectView = objectViewFactories.createObjectView(className, xml);
                    if(objectView != nullptr)
                    {
                        objectView->setParent(window);
                    }

                    //if (className == "EllipseView") {
                    //    EllipseView *ellipseView = ellipseViewFactory.createObjectView(xml);
                    //    ellipseView->setParent(window);
                    //}
                    //else if (className == "RectangleView") {
                    //    RectangleView *rectangleView = rectangleViewFactory.createObjectView(xml);
                    //    rectangleView->setParent(window);
                    //}
                    //else if (className == "PolygonView") {
                    //    PolygonView *polygonView = polygonViewFactory.createObjectView(xml);
                    //    polygonView->setParent(window);
                    //}
                }
            }
        }

        window->show();
    }

    void XMLParser::save()
    {
    }
}
