#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QPainterPath>

namespace trei {
    class Window : public QWidget
    {
        Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        ~Window();

    private:
        QPainterPath trianglePath;
    };
}
#endif // WINDOW_H
