#include "xmlparser.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamEntityDeclaration>

#include <QFile>
#include <QDebug>

namespace trei
{
    QList<Window*> XMLParser::load()
    {
        QFile file(":/resources/figure.xml");
        QList<Window*> windows;

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Error open file to read! Error = " << file.errorString();
            return windows;
        }

        QXmlStreamReader xml(&file);
        Window *window = nullptr;

        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartDocument)
            {
                continue;
            }

            if (token == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "window")
                {
                    window = objectViewFactories.createWindow(xml);
                    windows.append(window);

                    continue;
                }

                if (xml.name() == "objectView")
                {
                    QString className = xml.attributes().value("class").toString();
                    ObjectView *objectView = objectViewFactories.createObjectView(className, xml);

                    QString str = typeid(*objectView).name();
                    QString str2 = objectView->metaObject()->className();
                    int ind2 = str2.lastIndexOf("::") + 2;
                    QString str3 = "A::B::PolygonView";
                    int ind3 = str3.lastIndexOf("::") + 2;
                    QString subString2 = str2.mid(ind2); //
                    QString subString3 = str3.mid(ind3); // subString contains "is"
                    qDebug() << str << " | " << str2 << " = " << ind2 << " | " << str3 << " = " << ind3;
                    qDebug() << subString2 << " | " << subString3;

                    if (objectView != nullptr)
                    {
                        window->addObjectView(objectView);
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

        for(int i = 0; i < windows.size(); i++)
        {
            windows[i]->show();
        }

        file.close();

        return windows;
    }

    void XMLParser::save(QList<Window*> windows) const
    {
        QString filePath = QDir::currentPath() + "/figure_copy_copy.xml";
        qDebug() << filePath;

        QFileInfo fileInfo(filePath);
        QFile file(filePath);

        if (!fileInfo.exists())
        {
            qDebug() << "File for write not exist";
            //TODO: create file
        }

        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Error open file to write! Error = " << file.errorString();
            return;
        }

        QXmlStreamWriter xml(&file);

        xml.setAutoFormatting(true);
        xml.writeStartDocument();

        for(int i = 0; i < windows.size(); i++)
        {
            QByteArray partXml = objectViewFactories.windowToXML(*windows[i]);
            file.write(partXml);
        }
        xml.writeEndDocument();

        //xml.writeStartElement("scene");

        ////for (SceneObject *object : objects)
        ////{
        //xml.writeStartElement("object");
        //xml.writeAttribute("type 1", "aa");
        //xml.writeAttribute("type 2", "bbb");
        //xml.writeAttribute("type 3", "cccc");

        //xml.writeStartElement("script");
        //xml.writeEndElement();

        ////    xml.writeAttribute("x", QString::number(object->position.x()));
        ////    xml.writeAttribute("y", QString::number(object->position.y()));
        ////    xml.writeAttribute("width", QString::number(object->width));
        ////    xml.writeAttribute("height", QString::number(object->height));
        ////    xml.writeAttribute("color", object->color.name());
        ////    xml.writeAttribute("fillColor", object->fillColor.name());
        //xml.writeEndElement();
        ////}
        //xml.writeEndElement();

        //xml.writeEndElement();

        //xml.writeEndDocument();

        file.close();
    }
}
