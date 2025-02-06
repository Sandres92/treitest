#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>

#include "objectview.h"

namespace trei {
    class RectangleView: public ObjectView
    {
         Q_OBJECT
    //public:
    //    RectangleView();
     public:
         RectangleView();
         ~RectangleView();

    protected:
        void paintEvent(QPaintEvent *) override;
        void mousePressEvent(QMouseEvent *event) override;
    };
}
#endif // RECTANGLEVIEW_H
