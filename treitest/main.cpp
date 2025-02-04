#include <QCoreApplication>
#include <QDebug>

#include <QtWidgets>
#include "window.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication app(argc, argv);

    Window w;
    w.resize(320, 240);
    w.setWindowTitle(
        QApplication::translate("hello", "hello window"));

    w.show();

    return app.exec();
}
