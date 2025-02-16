#include "window.h"

#include <Window.h>

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
        copyObjectView = nullptr;

        delete centralWidget;
        delete dockWidget;

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
        QMenuBar* mainMenu = this->menuBar();
        QMenu *fileMenu = new QMenu("Файл");

        fileMenu->addMenu(createCreationMenu());

        QAction* saveAction = new QAction("Сохранить");
        connect(saveAction, SIGNAL(triggered()), this, SLOT(onSaveAction()));
        fileMenu->addAction(saveAction);

        mainMenu->addMenu(fileMenu);
    }

    QMenu *Window::createCreationMenu()
    {
        QMenu *creationMenu = new QMenu("Создать");
        QAction* createEllipsAction = new QAction("Элипс");
        creationMenu->addAction(createEllipsAction);
        QAction* createRectangleAction = new QAction("Квадрат");
        creationMenu->addAction(createRectangleAction);
        QAction* createPoligoneAction = new QAction("Полигон");
        creationMenu->addAction(createPoligoneAction);
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
        variantManager = new QtVariantPropertyManager();
        QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();
        propertyBrowser = new QtTreePropertyBrowser();

        propertyBrowser->setFactoryForManager(variantManager, variantFactory);

        dockWidget = new QDockWidget("Свойства", this);
        dockWidget->setWidget(propertyBrowser);
        dockWidget->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
        addDockWidget(Qt::RightDockWidgetArea, dockWidget);
        dockWidget->hide();
    }

    void Window::contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu menu(this);        
        menu.addMenu(createCreationMenu());

        QAction *pasteAction = menu.addAction("Вставить");
        pasteAction->setData(event->pos());

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
        hidePropertyBrowser();
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

        connect(objectView, SIGNAL(onEndDrag(ObjectView *)), this, SLOT(onEndDragObjectView(ObjectView *)));
    }

    const QList<ObjectView *> Window::getObjectViews() const
    {
        return objectViews;
    }

    void Window::onClickObjectView(ObjectView * objectView)
    {
        if(objectView == selectedObjectView)
        {
            return;
        }

        unselectObjectView();
        selectObjectView(objectView);
    }

    void Window::selectObjectView(ObjectView * objectView)
    {
        selectedObjectView = objectView;
        showPropertyBrowser(objectView);
    }

    void Window::unselectObjectView()
    {
        if(selectedObjectView)
        {
            selectedObjectView->unselect();
        }

        selectedObjectView = nullptr;
    }

    void Window::onCopyObjectView(ObjectView * objectView)
    {
        copyObjectView = objectView;
    }

    void Window::onDuplicateObjectView(ObjectView * objectView)
    {
        ObjectView* newObjectView  = objectView->clone();
        float posx = newObjectView->getPosx() + 10.f;
        float posy = newObjectView->getPosy() + 10.f;

        newObjectView->setPos(posx, posy);
        newObjectView->select();

        addObjectView(newObjectView);

        unselectObjectView();
    }

    void Window::onDeleteObjectView(ObjectView * objectView)
    {
        unselectObjectView();

        objectViews.removeOne(objectView);
        objectView->deleteLater();

        hidePropertyBrowser();
    }

    void Window::onEndDragObjectView(ObjectView * objectView)
    {
        QSet<QtProperty *> properties = variantManager->properties();
        QList<QtProperty *> posProperties;


        auto itPosx = std::find_if(properties.begin(), properties.end(),
                               [](const QtProperty* prop) {
                                   return prop->propertyName() == "posx";
                               });

        if (itPosx != properties.end())
        {
            QtProperty* foundProp = *itPosx;
            QVariant value(objectView->getPosx());

            variantManager->setValue(foundProp, value);
        }

        auto itPosy = std::find_if(properties.begin(), properties.end(),
                               [](const QtProperty* prop) {
                                   return prop->propertyName() == "posy";
                               });
        if (itPosy != properties.end())
        {
            QtProperty* foundProp = *itPosy;
            QVariant value(objectView->getPosy());

            variantManager->setValue(foundProp, value);
        }
    }

    void Window::createObjectView(const QPoint &pos)
    {

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

        unselectObjectView();
        selectObjectView(newObjectView);

        copyObjectView = selectedObjectView;
    }

    void Window::onHotKeyDuplicate()
    {
        if(!selectedObjectView)
        {
            return;
        }

        onDuplicateObjectView(selectedObjectView);
    }

    void Window::onHotKeyCopy()
    {
        if(!selectedObjectView)
        {
            return;
        }
        onCopyObjectView(selectedObjectView);
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

    void Window::onHotKeyDelete()
    {
        if(!selectedObjectView)
        {
            return;
        }

        onDeleteObjectView(selectedObjectView);
    }

    void Window::onSaveAction()
    {
        qDebug() << "save";
    }

    void Window::onPropertyAction()
    {

    }

    void Window::showPropertyBrowser(const ObjectView *objectView)
    {
        if(dockWidget->isHidden())
        {
            dockWidget->show();
        }
        loadPropertyBrowser(objectView);
    }

    void Window::hidePropertyBrowser()
    {
        dockWidget->hide();
        variantManager->clear();
        propertyBrowser->clear();
        disconnect(variantManagerConnection);
    }

    void Window::loadPropertyBrowser(const ObjectView *objectView)
    {
        disconnect(variantManagerConnection);

        variantManager->clear();
        propertyBrowser->clear();

        const QMetaObject *metaObject = objectView->metaObject();
        const QMetaObject *objectViewMeta = &ObjectView::staticMetaObject;
        int firstPropertyIndex = objectViewMeta->propertyOffset();

        for (int i = firstPropertyIndex; i < metaObject->propertyCount(); ++i) {

            QMetaProperty property = metaObject->property(i);
            if (!property.isReadable())
            {
                continue;
            }

            QVariant value = property.read(objectView);

            if (property.userType() == qMetaTypeId<QVariantList>())
            {
                QtVariantProperty *arrayProp = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), property.name());

                QVariantList array = value.toList();
                for (int j = 0; j < array.size(); ++j)
                {
                    QString pointName = QString("%1").arg(j);
                    QVariant q = array[j];
                    QtVariantProperty *arrayElementProperty = variantManager->addProperty(q.type(), pointName);
                    arrayElementProperty->setValue(q);
                    arrayProp->addSubProperty(arrayElementProperty);
                }

                propertyBrowser->addProperty(arrayProp);
            }
            else
            {
                QtVariantProperty *prop = variantManager->addProperty(value.type(), property.name());
                prop->setValue(value);
                propertyBrowser->addProperty(prop);
            }
        }

        variantManagerConnection =
            connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(propertyBrowserValueChanged(QtProperty *, const QVariant &)));
    }

    void Window::propertyBrowserValueChanged(QtProperty *property, const QVariant &value)
    {
        if(!selectedObjectView)
        {
            return;
        }

        const QMetaObject *metaObject = selectedObjectView->metaObject();

        int propertyIndex = metaObject->indexOfProperty(property->propertyName().toStdString().c_str());

        if(propertyIndex != -1)
        {
            QMetaProperty metaProperty = metaObject->property(propertyIndex);
            if (metaProperty.userType() == qMetaTypeId<QVariantList>())
            {

            }
            else
            {
                metaProperty.write(selectedObjectView, value);
            }
        }
    }
}

