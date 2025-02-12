#include "window.h"

namespace trei
{
    Window::Window(QWidget *parent)
        : QWidget(parent)
    {
    }

    Window::Window(const QString &name, const QColor &color, int type, int windowWidth, int windowHeight,
                   bool usePassword, const QString &password, const QString &groupName, const QString &subGroupName,
                   int posx, int posy, int accessLevel, QWidget *parent)
        : QWidget(parent), name(name), color(color), type(type),  windowWidth(windowWidth), windowHeight(windowHeight),
          usePassword(usePassword),  password(password), groupName(groupName), subGroupName(subGroupName),
          posx(posx), posy(posy), accessLevel(accessLevel)
    {
        setWindowTitle(name);
        resize(windowWidth, windowHeight);
        move(posx, posy);

        setStyleSheet("background-color:" + color.name() + ";");
    }

    Window::~Window()
    {
        qDeleteAll(objectViews);
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
        objectView->setParent(this);
    }

    const QList<ObjectView *> Window::getObjectViews() const
    {
        return objectViews;
    }
}
