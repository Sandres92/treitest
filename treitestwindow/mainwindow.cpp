#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initXmlParcer();

    initHotKey();
    init();
}

MainWindow::~MainWindow()
{
    delete keyCtrlS;

    if (xmlThread) {
        xmlThread->quit();
        xmlThread->wait();
        delete xmlThread;
    }

    delete xMLParser;

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

void MainWindow::initXmlParcer()
{
    xMLParser = new XMLParser();
    xmlThread = new QThread(this);

    xMLParser->moveToThread(xmlThread);

    connect(xmlThread, &QThread::started, xMLParser, &XMLParser::load);
    connect(xMLParser, &XMLParser::xmlLoaded, this, &MainWindow::onXMLLoaded);
}

void MainWindow::slotShortcutCtrlS()
{
    qDebug() << "ctrl + S";
    saveXML();
}

void MainWindow::loadXML()
{
    //QFuture<QList<Window *>> future = QtConcurrent::run([this]() {
    //    return xMLParser.load();
    //});
    //future.waitForFinished();
    //windows = future.result();

    //for (int i = 0; i < windows.size(); i++)
    //{
    //    windows[i]->show();
    //}

    xmlThread->start();
}

void MainWindow::onXMLLoaded(QList<Window *> windows)
{
    windows = xMLParser->load();
}

void MainWindow::saveXML()
{
    QtConcurrent::run([this]() {
        xMLParser->save(this->windows);
    });
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

