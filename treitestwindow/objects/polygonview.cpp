#include "polygonview.h"

#include <QPainter>
#include <QDebug>

namespace trei
{
    PolygonView::PolygonView(): ObjectView("Полигон")
    { }

    PolygonView::PolygonView(const QString &name, float posx, float posy) : ObjectView(name, posx, posy, 118.f, 98.f, 0, false,
                QColor(0, 0, 0, 255), 2, true, QColor(51, 77, 179, 255))
    {
        setCoords(QVector<QPointF> {{0.f, 49.f}, {59.f, 0.f}, {118.f, 73.5f}, {59.f, 98.f}});
    }

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

    void PolygonView::mousePressEventHandler()
    {
    }

    QVector<QPointF> PolygonView::getCoords() const
    {
        return coords;
    }

    QString PolygonView::getCoordsString() const
    {
        QStringList points;

        for (int i = 0; i < coords.size(); i++)
        {
            points.append(QString("(%1, %2)").arg(coords[i].x()).arg(coords[i].y()));
        }

        return points.join("; ");
    }

    QVariantList PolygonView::getCoordsAsVariantList() const
    {
        QVariantList list;

        for (int i = 0; i < coords.size(); i++)
        {
            list.append(QVariant::fromValue(coords[i]));
        }

        return list;
    }

    void PolygonView::setCoordsFromVariantList(const QVariantList &coordsVariantList)
    {
        coords.clear();

        for (int i = 0; i < coordsVariantList.size(); i++)
        {
            coords.append(coordsVariantList[i].toPointF());
        }

        repaint();
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

    PolygonView *PolygonView::clone()
    {
        PolygonView *newObjectView = new PolygonView(this->name, this->posx, this->posy, this->width,
                                                     this->height, this->angle, this->lock, this->lineColor,
                                                     this->lineWidth, this->fill, this->fillColor);
        newObjectView->setParent(this->parentWidget());
        newObjectView->setCoords(this->coords);

        return newObjectView;
    }

    void PolygonView::saveToStream(QDataStream &out) const
    {
        ObjectView::saveToStream(out);
        out << coords;
    }

    void PolygonView::loadFromStream(QDataStream &in)
    {
        ObjectView::loadFromStream(in);
        in >> coords;
    }
}
