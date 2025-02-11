#include "polygonview.h"

#include <QPainter>
#include <QDebug>

namespace trei
{
    PolygonView::PolygonView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                             const QColor &lineColor, int linewidth, bool fill, const QColor &fillColor)
        : ObjectView(name, posx, posy, width, height, angle, lock, lineColor, linewidth, fill, fillColor)
    {

    }

    void PolygonView::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        if (fill)
        {
            painter.setBrush(fillColor);
        }

        painter.setPen(QPen(lineColor, lineWidth));

        QPolygonF polygon(coords);
        painter.drawPolygon(polygon);
    }

    void PolygonView::mousePressEvent(QMouseEvent *event)
    {
        qDebug() << "EllipseView::mousePressEvent";
    }

    QVector<QPointF> PolygonView::getCoords() const
    {
        return coords;
    }

    void PolygonView::addCoord(const QPointF &coord)
    {
        coords.append(coord);
        repaint();
    }

    void PolygonView::setCoords(const QVector<QPointF> &coords)
    {

        this->coords = coords;
        repaint();
    }
}
