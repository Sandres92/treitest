#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QString>

#include "objects/objectview.h"
#include <QList>

#include <qttreepropertybrowser.h>
#include <qtvariantproperty.h>

namespace trei
{
    class Window : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        explicit Window(const QString &name, const QColor &color, int type, int windowWidth, int windowHeight,
                        bool usePassword, const QString &password, const QString &groupName, const QString &subGroupName,
                        int posx, int posy, int accessLevel, QWidget *parent = 0);

        ~Window();

        void setName(const QString &name);
        QString getName() const;
        void setColor(const QColor &color);
        QColor getColor() const;
        void setType(int type);
        int getType() const;
        void setWindowWidth(int windowWidth);
        int getWindowWidth() const;
        void setWindowHeight(int windowHeight);
        int getWindowHeight() const;
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

        void addObjectView(ObjectView *objectView);
        const QList<ObjectView *> getObjectViews() const;

    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;

    private slots:
        void paste(const QPoint &pos);
        void onObjectViewClick(ObjectView * objectView);
        void onObjectViewCopy(ObjectView * objectView);
        void onObjectViewDuplicate(ObjectView * objectView);

        void onHotKeyDuplicate();
        void onHotKeyCopy();
        void onHotKeyPaste();
        void onSaveAction();
        void onPropertyAction();

    private:
        QString name;
        QColor color;
        int type;
        int windowWidth;
        int windowHeight;
        bool usePassword;
        QString password;
        QString groupName;
        QString subGroupName;
        int posx;
        int posy;
        int accessLevel;

        QList<ObjectView *> objectViews;
        ObjectView * selectedObjectView = nullptr;
        void unselectObjectView(ObjectView * objectView);

        ObjectView* copyObjectView = nullptr;

        QShortcut *keyCtrlD;
        QShortcut *keyCtrlC;
        QShortcut *keyCtrlV;
        void initHotKey();

        void init_qtbrowserproperty();
        void initWindow();

        QWidget *centralWidget;
        QDockWidget *dockWidget;
        QtTreePropertyBrowser *propertyBrowser;
        void loadPropertiesToBrowser(QtTreePropertyBrowser *browser, ObjectView *object);
    };
}
#endif // WINDOW_H
