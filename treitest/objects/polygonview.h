#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QPointF>

#include "objectview.h"

namespace trei
{
    class PolygonView: public ObjectView
    {
        public:
            explicit PolygonView();
            explicit PolygonView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                                   const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);
            ~PolygonView();

            void addCoord(const QPointF &coord);
            void setCoords(const QVector<QPointF> &coords);

        protected:
            void paintEvent(QPaintEvent *) override;
            void mousePressEvent(QMouseEvent *event) override;

        private:
            QVector<QPointF> coords;
    };
}
#endif // POLYGONVIEW_H
