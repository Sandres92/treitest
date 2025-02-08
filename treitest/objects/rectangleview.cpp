#include "rectangleview.h"
#include <QPainter>
#include <QDebug>

namespace trei
{
    RectangleView::RectangleView()
    {
        qDebug()<< "RectangleView 1";
    }

    RectangleView::RectangleView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                                 const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor)
        :ObjectView(name, posx, posy, width, height, angle, lock, lineColor, lineWidth, fill, fillColor)
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
        //qDebug() << "lineWidth "<< lineWidth;

        painter.setPen(QPen(lineColor, lineWidth));

        QRect rect (0.f, 0.f, width, height);

        //QPolygonF rect;
        //rect << QPointF(0.f, 0.f)
        //         << QPointF(width, 0.f)
        //         << QPointF(width, height)
        //         << QPointF(0.f, height)
        //         << QPointF(0.f//

        painter.drawRect(rect);
    }

    void RectangleView::mousePressEvent(QMouseEvent *event)
    {
        qDebug() <<"RectangleView::mousePressEvent";
    }
}
