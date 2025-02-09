#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>
#include <QColor>

namespace trei
{
    class ObjectView: public QWidget
    {
        Q_OBJECT

        public:
            explicit ObjectView() = default;
            explicit ObjectView(const QString &name, float posx, float posy, float width, float height,
                                int angle, bool lock, const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);

            virtual ~ObjectView() = default;

            void setName(const QString &name);
            void setPosx(float posx);
            void setPosy(float posy);
            void setWidth(float width);
            void setHeight(float height);
            void setAngle(int angle);
            void setLock(bool lock);
            void setLineColor(const QColor &lineColor);
            void setLineWidth(int lineWidth);
            void setFill(bool fill);
            void setFillColor(const QColor &fillColor);

            void setPos(float posx, float posy);
            void setSize(float width, float height);

            QString getName() const;
            float getPosx() const;
            float getPosy() const;
            float getWidth() const;
            float getHeight() const;
            int getAngle() const;
            bool getLock() const;
            QColor getLineColor() const;
            int getLineWidth() const;
            bool getFill() const;
            QColor getFillColor() const;

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
