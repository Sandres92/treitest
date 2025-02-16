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
    delete keyCtrlZ;
    delete keyCtrlD;
    delete keyCtrlC;
    delete keyCtrlV;

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

    keyCtrlZ = new QShortcut(this);
    keyCtrlZ->setKey(Qt::CTRL + Qt::Key_Z);
    connect(keyCtrlZ, SIGNAL(activated()), this, SLOT(slotShortcutCtrlZ()));

    keyCtrlD = new QShortcut(this);
    keyCtrlD->setKey(Qt::CTRL + Qt::Key_D);
    connect(keyCtrlD, SIGNAL(activated()), this, SLOT(slotShortcutCtrlD()));

    keyCtrlC = new QShortcut(this);
    keyCtrlC->setKey(Qt::CTRL + Qt::Key_C);
    connect(keyCtrlC, SIGNAL(activated()), this, SLOT(copy()));

    keyCtrlV = new QShortcut(this);
    keyCtrlV->setKey(Qt::CTRL + Qt::Key_V);
    connect(keyCtrlV, SIGNAL(activated()), this, SLOT(paste()));
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

void MainWindow::slotShortcutCtrlD()
{
    qDebug() << "ctrl + D";
}

void MainWindow::loadXML()
{
    windows = xMLParser.load();
}

void MainWindow::saveXML()
{
    xMLParser.save(windows);
}
