#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolBar>
#include <QDockWidget>

#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initHotKey();
    init();

    init_qtbrowserproperty();
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

void MainWindow::init_qtbrowserproperty()
{
    QtVariantPropertyManager *variantManager = new QtVariantPropertyManager();
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
    QtTreePropertyBrowser *propertyBrowser = new QtTreePropertyBrowser();

    propertyBrowser->setFactoryForManager(variantManager, variantFactory);

    QtVariantProperty *property1 = variantManager->addProperty(QVariant::String, "Имя объекта");
    property1->setValue("TestObject");

    QtVariantProperty *property2 = variantManager->addProperty(QVariant::Double, "Размер");
    property2->setValue(10.5);

    propertyBrowser->addProperty(property1);
    propertyBrowser->addProperty(property2);

    QDockWidget *dockWidget = new QDockWidget("Свойства", this);
    dockWidget->setWidget(propertyBrowser);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
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
