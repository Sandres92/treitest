#include "rectangleview.h"
#include <QPainter>

//RectangleView::RectangleView() {
//    qDebug() << "hello !";
//}

void RectangleView::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.setBrush(Qt::blue);

    QPolygonF triangle;
    triangle << QPointF(50, 0)
             << QPointF(0, 100)
             << QPointF(100, 100)
             << QPointF(50, 0);

    painter.drawPolygon(triangle);

    resize(100, 100);
}

void RectangleView::mousePressEvent(QMouseEvent *event)
{
    qDebug() <<"RectangleView::mousePressEvent";
}
