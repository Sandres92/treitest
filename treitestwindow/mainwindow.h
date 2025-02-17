#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xmlparser.h"

#include <QSplitter>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

using namespace trei;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotShortcutCtrlS();

private:
    Ui::MainWindow *ui;

    void loadXML();
    void saveXML();

    XMLParser xMLParser;
    QList<Window *> windows;

    QShortcut *keyCtrlS;

    void initHotKey();
    void saveWindow();
    void saveAllWindow();
    void init();
};
#endif // MAINWINDOW_H
