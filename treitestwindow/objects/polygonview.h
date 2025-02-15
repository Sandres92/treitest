#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>
#include <QVector>
#include <QPointF>

#include "objectview.h"
#include <QVariantList>

namespace trei
{
    class PolygonView: public ObjectView
    {
        Q_OBJECT
        //Q_PROPERTY(QString coords READ getCoordsString)
        //Q_PROPERTY(QVector<QPointF> coords READ getCoords)
        Q_PROPERTY(QVariantList coords READ getCoordsVL)

    public:
        explicit PolygonView() = default;
        explicit PolygonView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                             const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);
        ~PolygonView() = default;

        void setCoords(const QVector<QPointF> &coords);
        void addCoord(const QPointF &coord);
        QVector<QPointF> getCoords() const;
        QString getCoordsString() const;
        QVariantList getCoordsVL() const;
        PolygonView *clone() override;

    protected:
        void paintEvent(QPaintEvent *) override;
        void mousePressEventHandler() override;

    private:
        QVector<QPointF> coords;
    };
}
#endif // POLYGONVIEW_H
