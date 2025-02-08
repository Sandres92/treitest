#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>
#include <QColor>

namespace trei {
    class ObjectView: public QWidget
    {
        Q_OBJECT

        public:
            explicit ObjectView();
            explicit ObjectView(const QString &name, float posx, float posy, float width, float height,
                                int angle, bool lock, const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);

            ~ObjectView();

            void setName(const QString &name);
            void setPosx(float posx);
            void setPosy(float posy);
            void setWidth(float width);
            void setHeight(float height);
            void setLineWidth(int lineWidth);

            void setPos(float posx, float posy);
            void setSize(float width, float height);

            QString getName(QString name) const;
            float getPosx(float posx) const;
            float getPosy(float posy) const;
            float getWidth(float width) const;
            float getHeight(float height) const;
            int getLinewidth(int linewidth) const;

        protected:
            QString name;
            float posx;
            float posy;
            float width;
            float height;
            int angle;
            bool lock;
            QColor lineColor;
            int lineWidth;
            bool fill;
            QColor fillColor;
    };
}
#endif // OBJECTVIEW_H
