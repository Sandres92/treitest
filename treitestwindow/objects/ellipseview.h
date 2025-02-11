#ifndef ELLIPSEVIEW_H
#define ELLIPSEVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>

#include "objectview.h"

namespace trei
{
    class EllipseView: public ObjectView
    {
        Q_OBJECT

        public:
            explicit EllipseView();
            explicit EllipseView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                                   const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);

            ~EllipseView();

        protected:
            void paintEvent(QPaintEvent *) override;
            void mousePressEvent(QMouseEvent *event) override;
    };
}
#endif // ELLIPSEVIEW_H
