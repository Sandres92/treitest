#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initHotKey();
    init();
}

MainWindow::~MainWindow()
{
    delete keyCtrlS;

    delete ui;
}

void MainWindow::init()
{
    loadXML();
}

void MainWindow::initHotKey()
{
    keyCtrlS = new QShortcut(this);
    keyCtrlS->setKey(Qt::CTRL + Qt::Key_S);
    connect(keyCtrlS, SIGNAL(activated()), this, SLOT(slotShortcutCtrlS()));
}

void MainWindow::slotShortcutCtrlS()
{
    qDebug() << "ctrl + S";
    saveXML();
}

void MainWindow::loadXML()
{
    windows = xMLParser.load();
}

void MainWindow::saveXML()
{
    xMLParser.save(windows);
}

void MainWindow::on_actionSave_triggered()
{
    saveXML();
}

void MainWindow::on_actionNew_triggered()
{
    createNewWindow();
}

void MainWindow::createNewWindow()
{
    int countWindiws = windows.size();

    Window *newWindow = WindowFactory::instance().createWindow(countWindiws);
    windows.append(newWindow);
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

