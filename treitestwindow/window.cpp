#include "window.h"

#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>

namespace trei
{
    Window::Window(QWidget *parent)
        : QMainWindow(parent)
    {
        initWindow();
        initHotKey();
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

        initHotKey();
        init_qtbrowserproperty();
    }

    Window::~Window()
    {
        delete keyCtrlD;
        delete keyCtrlC;
        delete keyCtrlV;

        selectedObjectView = nullptr;
        copyObjectView = nullptr;

        qDeleteAll(objectViews);
    }

    void Window::initWindow()
    {
        centralWidget = new QWidget();
        setCentralWidget(centralWidget);

        //QMenuBar *menu = new QMenuBar(this);
        //QMenu *file = new QMenu();
        //file->addMenu("&File");
        //menu->addMenu(file);

        QMenuBar* mainMenu = this->menuBar();

        QMenu *menuGame = new QMenu("Файл");
        menuGame->addAction("Сохранить");
        menuGame->addAction("Свойства");

        //QMenu *menuHelp = new QMenu("Help");
        //menuHelp->addAction("How to Play...");
        //menuHelp->addAction("About");

        mainMenu->addMenu(menuGame);
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
    }

    void Window::init_qtbrowserproperty()
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

    void Window::contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu menu(this);

        QAction *pasteAction = menu.addAction("Вставить");
        pasteAction->setData(event->pos());

        //menu.addAction("Вставить", this, &Window::paste);

        connect(pasteAction, &QAction::triggered, this, [this, pasteAction]() {
            QPoint pos = pasteAction->data().toPoint();
            paste(pos);
        });

        menu.exec(event->globalPos());
    }

    void Window::mousePressEvent(QMouseEvent *event)
    {
        for (ObjectView *obj : objectViews) {
            obj->unselect();
        }
        selectedObjectView = nullptr;

        //for (ObjectView *obj : objectViews) {
        //    if (obj->geometry().contains(event->pos())) {
        //        //selectedObject = obj;
        //        qDebug() << "Объект выбран:" << obj;
        //        break;
        //    }
        //}
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

        connect(objectView, SIGNAL(onObjectViewClick(ObjectView *)), this, SLOT(onObjectViewClick(ObjectView *)));
        connect(objectView, SIGNAL(onObjectViewCopy(ObjectView *)), this, SLOT(onObjectViewCopy(ObjectView *)));
        connect(objectView, SIGNAL(onObjectViewDuplicate(ObjectView *)), this, SLOT(onObjectViewDuplicate(ObjectView *)));
    }

    const QList<ObjectView *> Window::getObjectViews() const
    {
        return objectViews;
    }

    void Window::onObjectViewClick(ObjectView * objectView)
    {
        if(objectView == selectedObjectView)
        {
            return;
        }
        unselectObjectView(objectView);
    }

    void Window::unselectObjectView(ObjectView * objectView)
    {
        if(selectedObjectView)
        {
            selectedObjectView->unselect();
        }

        selectedObjectView = objectView;
    }

    void Window::onObjectViewCopy(ObjectView * objectView)
    {
        copyObjectView = objectView;
    }

    void Window::onObjectViewDuplicate(ObjectView * objectView)
    {
        ObjectView* newObjectView  = objectView->clone();
        float posx = newObjectView->getPosx() + 10.f;
        float posy = newObjectView->getPosy() + 10.f;

        newObjectView->setPos(posx, posy);
        newObjectView->select();

        addObjectView(newObjectView);

        unselectObjectView(newObjectView);
    }

    void Window::paste(const QPoint &pos)
    {
        if(!copyObjectView)
        {
            return;
        }

        ObjectView* newObjectView  = copyObjectView->clone();
        float posx = pos.x();
        float posy = pos.y();

        newObjectView->setPos(posx, posy);
        newObjectView->select();

        addObjectView(newObjectView);

        unselectObjectView(newObjectView);

        copyObjectView = selectedObjectView;
    }

    void Window::onHotKeyDuplicate()
    {
        if(!selectedObjectView)
        {
            return;
        }

        onObjectViewDuplicate(selectedObjectView);
    }

    void Window::onHotKeyCopy()
    {
        if(!selectedObjectView)
        {
            return;
        }
        onObjectViewCopy(selectedObjectView);
    }

    void Window::onHotKeyPaste()
    {
        if(!copyObjectView)
        {
            return;
        }

        float posx = copyObjectView->getPosx() + 10.f;
        float posy = copyObjectView->getPosy() + 10.f;

        paste(QPoint(posx, posy));
    }
}
