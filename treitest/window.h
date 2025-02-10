#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QString>

namespace trei {
    class Window : public QWidget
    {
        Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        ~Window();

        void setName(const QString &name);
        QString getName() const;
        void setColor(const QColor &color);
        QColor getColor() const;
        void setType(int type);
        int getType() const;
        void setWindowHeight(int windowHeight);
        int getWindowHeight() const;
        void setWindowWidth(int windowWidth);
        int getWindowWidth() const;
        void setSize(int windowHeight, int windowWidth);
        void setUsePassword(bool usePassword);
        bool getUsePassword() const;
        void setPassword(const QString &password);
        QString getPassword() const;
        void setGroupName(const QString &groupName);
        QString getGroupName() const;
        void setSubGroupName(const QString &subGroupName);
        QString getSubGroupName() const;
        void setPosx(int posx);
        int getPosx() const;
        void setPosy(int posy);
        int getPosy() const;
        void setPos(int posx, int posy);
        void setAccessLevel(int accessLevel);
        int getAccessLevel() const;

    private:
        QString name;
        QColor color;
        int type;
        int windowHeight;
        int windowWidth;
        bool usePassword;
        QString password;
        QString groupName;
        QString subGroupName;
        int posx;
        int posy;
        int accessLevel;
    };
}
#endif // WINDOW_H
