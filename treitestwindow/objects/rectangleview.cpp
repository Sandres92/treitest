#include "rectangleview.h"
#include <QPainter>
#include <QDebug>

namespace trei
{
    RectangleView::RectangleView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                                 const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor)
        : ObjectView(name, posx, posy, width, height, angle, lock, lineColor, lineWidth, fill, fillColor)
    { }

    RectangleView::RectangleView(const QString &name, float posx, float posy) : ObjectView(name, posx, posy, 75.f, 75.f, 0, false,
                QColor(0, 0, 0, 255), 2, true, QColor(77, 128, 77, 255))
    { }

    void RectangleView::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        if (fill)
        {
            painter.setBrush(fillColor);
        }

        //qDebug() << "lineWidth "<< lineWidth;

        painter.setPen(QPen(lineColor, lineWidth));

        QRect rect(lineWidth / 2.f, lineWidth / 2.f, width - lineWidth / 2.f, height - lineWidth / 2.f);

        painter.drawRect(rect);
    }

    void RectangleView::mousePressEventHandler()
    {
    }

    RectangleView *RectangleView::clone()
    {
        RectangleView *newObjectView = new RectangleView(this->name, this->posx, this->posy, this->width,
                                                         this->height, this->angle, this->lock, this->lineColor,
                                                         this->lineWidth, this->fill, this->fillColor);
        newObjectView->setParent(this->parentWidget());
        return newObjectView;
    }
}
