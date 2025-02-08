#include "rectangleview.h"
#include <QPainter>
#include <QDebug>

namespace trei {
    RectangleView::RectangleView()
    {
        qDebug()<< "RectangleView 1";
    }

    RectangleView::RectangleView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                                 const QColor &lineColor, int linewidth, bool fill, const QColor &fillColor)
        :ObjectView(name, posx, posy, width, height, angle, lock, lineColor, linewidth, fill, fillColor)
    {

    }

    RectangleView::~RectangleView()
    {
    }

    void RectangleView::paintEvent(QPaintEvent *) {
        QPainter painter(this);

        if (fill){
            painter.setBrush(fillColor);
        }
        painter.setPen(QPen(lineColor, lineWidth));

        QPolygonF rect;
        rect << QPointF(0.f, 0.f)
                 << QPointF(width, 0.f)
                 << QPointF(width, height)
                 << QPointF(0.f, height)
                 << QPointF(0.f, 0.f);

        painter.drawPolygon(rect);
    }

    void RectangleView::mousePressEvent(QMouseEvent *event)
    {
        qDebug() <<"RectangleView::mousePressEvent";
    }
}
