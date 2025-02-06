#include "rectangleview.h"
#include <QPainter>
#include <QDebug>

namespace trei {
    RectangleView::RectangleView()
    {
        qDebug()<< "RectangleView ";
    }

    RectangleView::~RectangleView()
    {

    }

    void RectangleView::paintEvent(QPaintEvent *) {
        QPainter painter(this);

        painter.setBrush(Qt::blue);
        painter.setPen(QPen(Qt::cyan, 1));

        QPolygonF triangle;
        triangle << QPointF(width/2.f, 0.f)
                 << QPointF(0.f, height)
                 << QPointF(width, height)
                 << QPointF(width/2.f, 0.f);

        painter.drawPolygon(triangle);
    }

    void RectangleView::mousePressEvent(QMouseEvent *event)
    {
        qDebug() <<"RectangleView::mousePressEvent";
    }
}
