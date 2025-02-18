#include "window.h"

namespace trei
{
    Window::Window(QWidget *parent)
        : QMainWindow(parent)
    {
        initWindow();
    }

    Window::Window(const QString &name, const QColor &color, int type, int windowWidth, int windowHeight,
                   bool usePassword, const QString &password, const QString &groupName, const QString &subGroupName,
                   int posx, int posy, int accessLevel, QWidget *parent)
        : QMainWindow(parent), name(name), color(color), type(type),  windowWidth(windowWidth), windowHeight(windowHeight),
          usePassword(usePassword),  password(password), groupName(groupName), subGroupName(subGroupName),
          posx(posx), posy(posy), accessLevel(accessLevel)
    {
        initWindow();

        setWindowTitle(name);
        resize(windowWidth, windowHeight);
        move(posx, posy);

        centralWidget->setStyleSheet("background-color:" + color.name() + ";");
    }

    Window::~Window()
    {
        delete keyCtrlD;
        delete keyCtrlC;
        delete keyCtrlV;

        selectedObjectView = nullptr;
        //copyObjectView = nullptr;

        delete centralWidget;
        delete propertyBrowser;

        qDeleteAll(objectViews);
    }

    void Window::initWindow()
    {
        centralWidget = new QWidget();
        setCentralWidget(centralWidget);

        initHotKey();
        initQtPropertyBrowser();
        initMenuBar();
    }

    void Window::initMenuBar()
    {
        QMenuBar *mainMenu = this->menuBar();
        QMenu *fileMenu = new QMenu("Файл");

        fileMenu->addMenu(createCreationMenu(QPoint(windowWidth / 3.f, windowHeight / 3.f)));

        QAction *saveAction = new QAction("Сохранить");
        connect(saveAction, SIGNAL(triggered()), this, SLOT(onSaveAction()));
        fileMenu->addAction(saveAction);

        mainMenu->addMenu(fileMenu);
    }

    QMenu *Window::createCreationMenu(const QPoint &pos)
    {
        QMenu *creationMenu = new QMenu("Создать");
        QAction *createEllipsAction = new QAction("Эллипс");
        creationMenu->addAction(createEllipsAction);
        createEllipsAction->setData(pos);
        connect(createEllipsAction, &QAction::triggered, this, [this, createEllipsAction]()
        {
            const QPoint pos = createEllipsAction->data().toPoint();
            createObjectView("EllipseView", pos);
        });

        QAction *createRectangleAction = new QAction("Прямоугольник");
        creationMenu->addAction(createRectangleAction);
        createRectangleAction->setData(pos);
        connect(createRectangleAction, &QAction::triggered, this, [this, createRectangleAction]()
        {
            const QPoint pos = createRectangleAction->data().toPoint();
            createObjectView("RectangleView", pos);
        });

        QAction *createPoligoneAction = new QAction("Полигон");
        creationMenu->addAction(createPoligoneAction);
        createPoligoneAction->setData(pos);
        connect(createPoligoneAction, &QAction::triggered, this, [this, createPoligoneAction]()
        {
            const QPoint pos = createPoligoneAction->data().toPoint();
            createObjectView("PolygonView", pos);
        });

        return creationMenu;
    }

    void Window::initHotKey()
    {
        keyCtrlD = new QShortcut(this);
        keyCtrlD->setKey(Qt::CTRL + Qt::Key_D);
        connect(keyCtrlD, SIGNAL(activated()), this, SLOT(onHotKeyDuplicate()));

        keyCtrlC = new QShortcut(this);
        keyCtrlC->setKey(Qt::CTRL + Qt::Key_C);
        connect(keyCtrlC, SIGNAL(activated()), this, SLOT(onHotKeyCopy()));

        keyCtrlV = new QShortcut(this);
        keyCtrlV->setKey(Qt::CTRL + Qt::Key_V);
        connect(keyCtrlV, SIGNAL(activated()), this, SLOT(onHotKeyPaste()));

        keyCtrlDel = new QShortcut(this);
        keyCtrlDel->setKey(Qt::Key_Delete);
        connect(keyCtrlDel, SIGNAL(activated()), this, SLOT(onHotKeyDelete()));
    }

    void Window::initQtPropertyBrowser()
    {
        propertyBrowser = new PropertyBrowserDockWidget("Свойства", this);

        addDockWidget(Qt::RightDockWidgetArea, propertyBrowser);
    }

    void Window::contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu menu(this);
        menu.addMenu(createCreationMenu(QPoint(event->pos())));

        QAction *pasteAction = new QAction("Вставить");
        pasteAction->setData(event->pos());
        menu.addAction(pasteAction);

        connect(pasteAction, &QAction::triggered, this, [this, pasteAction]()
        {
            const QPoint pos = pasteAction->data().toPoint();
            paste(pos);
        });

        menu.exec(event->globalPos());
    }

    void Window::mousePressEvent(QMouseEvent *event)
    {
        propertyBrowser->hidePropertyBrowser();

        for (ObjectView *obj : objectViews)
        {
            obj->unselect();
        }

        selectedObjectView = nullptr;
    }

    void Window::setName(const QString &name)
    {
        this->name = name;
    }
    QString Window::getName() const
    {
        return name;
    }

    void Window::setColor(const QColor &color)
    {
        this->color = color;
    }
    QColor Window::getColor() const
    {
        return color;
    }

    void Window::setType(int type)
    {
        this->type = type;
    }
    int Window::getType() const
    {
        return type;
    }

    void Window::setWindowHeight(int windowHeight)
    {
        this->windowHeight = windowHeight;
    }
    int Window::getWindowHeight() const
    {
        return windowHeight;
    }

    void Window::setWindowWidth(int windowWidth)
    {
        this->windowWidth = windowWidth;
    }
    int Window::getWindowWidth() const
    {
        return windowWidth;
    }

    void Window::setSize(int windowWidth, int windowHeight)
    {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
    }

    void Window::setUsePassword(bool usePassword)
    {
        this->usePassword = usePassword;
    }
    bool Window::getUsePassword() const
    {
        return usePassword;
    }

    void Window::setPassword(const QString &password)
    {
        this->password = password;
    }
    QString Window::getPassword() const
    {
        return password;
    }

    void Window::setGroupName(const QString &groupName)
    {
        this->groupName = groupName;
    }
    QString Window::getGroupName() const
    {
        return groupName;
    }

    void Window::setSubGroupName(const QString &subGroupName)
    {
        this->subGroupName = subGroupName;
    }
    QString Window::getSubGroupName() const
    {
        return subGroupName;
    }

    void Window::setPosx(int posx)
    {
        this->posx = posx;
    }
    int Window::getPosx() const
    {
        return posx;
    }

    void Window::setPosy(int posy)
    {
        this->posy = posy;
    }
    int Window::getPosy() const
    {
        return posy;
    }

    void Window::setPos(int posx, int posy)
    {
        this->posx = posx;
        this->posy = posy;
    }

    void Window::setAccessLevel(int accessLevel)
    {
        this->accessLevel = accessLevel;
    }
    int Window::getAccessLevel() const
    {
        return accessLevel;
    }

    void Window::addObjectView(ObjectView *objectView)
    {
        objectViews.append(objectView);
        objectView->setParent(centralWidget);
        objectView->show();

        connect(objectView, SIGNAL(onClickObjectView(ObjectView *)), this, SLOT(onClickObjectView(ObjectView *)));
        connect(objectView, SIGNAL(onCopyObjectView(ObjectView *)), this, SLOT(onCopyObjectView(ObjectView *)));
        connect(objectView, SIGNAL(onDuplicateObjectView(ObjectView *)), this, SLOT(onDuplicateObjectView(ObjectView *)));
        connect(objectView, SIGNAL(onDeleteObjectView(ObjectView *)), this, SLOT(onDeleteObjectView(ObjectView *)));

        connect(objectView, SIGNAL(onEndDrag(const ObjectView *)), this, SLOT(onEndDragObjectView(const ObjectView *)));
    }

    const QList<ObjectView *> Window::getObjectViews() const
    {
        return objectViews;
    }

    void Window::onClickObjectView(ObjectView *objectView)
    {
        if (objectView == selectedObjectView)
        {
            return;
        }

        unselectObjectView();
        selectObjectView(objectView);
    }

    void Window::selectObjectView(ObjectView *objectView)
    {
        selectedObjectView = objectView;
        selectedObjectView->raise();

        propertyBrowser->showPropertyBrowser(objectView);
    }

    void Window::unselectObjectView()
    {
        if (selectedObjectView)
        {
            selectedObjectView->unselect();
        }

        selectedObjectView = nullptr;

        propertyBrowser->hidePropertyBrowser();
    }

    void Window::onCopyObjectView(ObjectView *objectView)
    {
        QByteArray copyBuffer;
        QDataStream out(&copyBuffer, QIODevice::WriteOnly);
        out << Convector::fulCalssNameToShort(objectView->metaObject()->className());
        out << *objectView;

        QClipboard *clipboard = QApplication::clipboard();
        clipboard->clear();

        QMimeData *mimeData = new QMimeData();
        mimeData->setData("application/x-objectview", copyBuffer);

        clipboard->setMimeData(mimeData);

        //copyObjectView = objectView;
    }

    void Window::onDuplicateObjectView(ObjectView *objectView)
    {
        ObjectView *newObjectView  = objectView->clone();
        float posx = newObjectView->getPosx() + 10.f;
        float posy = newObjectView->getPosy() + 10.f;

        newObjectView->setPos(posx, posy);
        newObjectView->select();

        addObjectView(newObjectView);

        unselectObjectView();
    }

    void Window::onDeleteObjectView(ObjectView *objectView)
    {
        unselectObjectView();

        objectViews.removeOne(objectView);
        objectView->deleteLater();

        propertyBrowser->hidePropertyBrowser();
    }

    void Window::onEndDragObjectView(const ObjectView *objectView)
    {
        propertyBrowser->updatePosPropertyBrowser(objectView);
    }

    void Window::createObjectView(const QString &className, const QPoint &pos)
    {
        ObjectView *newObjectView = ObjectViewFactories::instance().createObjectView(className, pos.x(), pos.y());
        addObjectView(newObjectView);
    }

    void Window::paste(const QPoint &pos)
    {
        const QMimeData *mimeData = QApplication::clipboard()->mimeData();

        if (!mimeData->hasFormat("application/x-objectview"))
        {
            return;
        }

        QByteArray copyBuffer = mimeData->data("application/x-objectview");
        QDataStream in(&copyBuffer, QIODevice::ReadOnly);
        QString className;
        in >> className;

        ObjectView *newObjectView = ObjectViewFactories::instance().createObjectView(className);

        if (newObjectView)
        {
            in >> *newObjectView;

            addObjectView(newObjectView);

            float posx = pos.x();
            float posy = pos.y();
            newObjectView->setPos(posx, posy);

            unselectObjectView();

            newObjectView->select();
            selectObjectView(newObjectView);
        }

        //if (!copyObjectView)
        //{
        //    return;
        //}
        //
        //ObjectView *newObjectView  = copyObjectView->clone();
        //float posx = pos.x();
        //float posy = pos.y();
        //
        //newObjectView->setPos(posx, posy);
        //newObjectView->select();
        //
        //addObjectView(newObjectView);
        //
        //unselectObjectView();
        //selectObjectView(newObjectView);
        //
        //copyObjectView = selectedObjectView;
    }

    void Window::onHotKeyDuplicate()
    {
        if (!selectedObjectView)
        {
            return;
        }

        onDuplicateObjectView(selectedObjectView);
    }

    void Window::onHotKeyCopy()
    {
        if (!selectedObjectView)
        {
            return;
        }

        onCopyObjectView(selectedObjectView);
    }

    void Window::onHotKeyPaste()
    {
        //if (!copyObjectView)
        //{
        //    return;
        //}
        const QMimeData *mimeData = QApplication::clipboard()->mimeData();

        if (!mimeData)
        {
            return;
        }

        //float posx = copyObjectView->getPosx() + 10.f;
        //float posy = copyObjectView->getPosy() + 10.f;
        paste(QPoint(windowWidth / 3.f, windowHeight / 3.f));
    }

    void Window::onHotKeyDelete()
    {
        if (!selectedObjectView)
        {
            return;
        }

        onDeleteObjectView(selectedObjectView);
    }

    void Window::onSaveAction()
    {
        qDebug() << "save";
    }
}

