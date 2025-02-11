#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>

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
    delete keyCtrlZ;
    delete ui;
}

void MainWindow::init() {
    loadXML();
}

void MainWindow::initHotKey()
{
    keyCtrlS = new QShortcut(this);
    keyCtrlS->setKey(Qt::CTRL + Qt::Key_S);
    connect(keyCtrlS, SIGNAL(activated()), this, SLOT(slotShortcutCtrlS()));

    keyCtrlZ = new QShortcut(this);
    keyCtrlZ->setKey(Qt::CTRL + Qt::Key_Z);
    connect(keyCtrlZ, SIGNAL(activated()), this, SLOT(slotShortcutCtrlZ()));
}


void MainWindow::slotShortcutCtrlS()
{
    qDebug() << "ctrl + S";
    saveXML();
}

void MainWindow::slotShortcutCtrlZ()
{
    qDebug() << "ctrl + Z";
}

void MainWindow::loadXML()
{
    windows = xMLParser.load();
}

void MainWindow::saveXML()
{
    xMLParser.save(windows);
}
