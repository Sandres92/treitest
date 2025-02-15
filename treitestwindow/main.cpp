#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QVector<QPointF>>("QVector<QPointF>");  // ✅ Регистрируем тип

    MainWindow w;
    w.show();

    return a.exec();
}
