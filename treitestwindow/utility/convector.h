#ifndef CONVECTOR_H
#define CONVECTOR_H

#include <QString>
#include <QColor>
#include <QRgb>
#include <QDebug>

namespace trei
{
    class Convector
    {
    public:
        static bool stringToBool(const QString &boolString) {
            return boolString.toLower() == "true" ? true : false;
        }

        static QString boolToString(bool value) {
            return value ? "true" : "false";
        }

        static QColor stringHexToColor(const QString &hexString) {
            //bool isOk = false;
            //QRgb rgba = hexString.toUInt(isOk, 16);
            QRgb rgba = hexString.toUInt(nullptr, 16);
            QRgb argb = ((rgba & 0xFF) << 24) | (rgba >> 8);

            //qDebug() << "QRgb:" << argb;
            //qDebug() << "Alpha:" << qAlpha(argb);
            //qDebug() << "Red:" << qRed(argb);
            //qDebug() << "Green:" << qGreen(argb);
            //qDebug() << "Blue:" << qBlue(argb);

            return QColor::fromRgba(argb);
        }

        static QString colorToHexColorString(const QColor &color) {
            uint alpha = color.alpha();
            uint red = color.red();
            uint green = color.green();
            uint blue = color.blue();

            return QString("0x%1%2%3%4").arg(red, 2, 16, QLatin1Char('0'))
                   .arg(green, 2, 16, QLatin1Char('0'))
                   .arg(blue, 2, 16, QLatin1Char('0'))
                   .arg(alpha, 2, 16, QLatin1Char('0'));
        }

        static QString fullCalssNameToShort(const QString &fullCalssName) {
            QString className = fullCalssName;
            int doubleColonIndex = fullCalssName.lastIndexOf("::");

            if (doubleColonIndex != -1) {
                className = className.mid(doubleColonIndex + 2);
            }

            return className;
        }
    };
}
#endif // CONVECTOR_H
