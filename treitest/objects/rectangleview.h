#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include <QDebug>
#include <QPaintDevice>
#include <QWidget>

class RectangleView: public QWidget
{
     Q_OBJECT
//public:
//    RectangleView();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // RECTANGLEVIEW_H
