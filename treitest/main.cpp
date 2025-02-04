#include <QCoreApplication>
#include <QDebug>

#include <QtWidgets>
#include "window.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QApplication app(argc, argv);

    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
        QApplication::translate("toplevel", "Top-level widget"));

    Window w;
    w.show();

    return app.exec();
}
