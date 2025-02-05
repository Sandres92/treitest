#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QPainterPath>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    QPainterPath trianglePath;
};

#endif // WINDOW_H
