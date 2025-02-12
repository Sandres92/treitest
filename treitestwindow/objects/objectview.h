#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>
#include <QColor>

namespace trei
{
    class ObjectView: public QWidget
    {
        Q_OBJECT

    public:
        explicit ObjectView() = default;
        explicit ObjectView(const QString &name, float posx, float posy, float width, float height,
                            int angle, bool lock, const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);
        virtual ~ObjectView() = default;

        virtual ObjectView *clone();

        void setName(const QString &name);
        QString getName() const;
        void setPosx(float posx);
        float getPosx() const;
        void setPosy(float posy);
        float getPosy() const;
        void setPos(float posx, float posy);
        void setWidth(float width);
        float getWidth() const;
        void setHeight(float height);
        float getHeight() const;
        void setSize(float width, float height);
        void setAngle(int angle);
        int getAngle() const;
        void setLock(bool lock);
        bool getLock() const;
        void setLineColor(const QColor &lineColor);
        QColor getLineColor() const;
        void setLineWidth(int lineWidth);
        int getLineWidth() const;
        void setFill(bool fill);
        bool getFill() const;
        void setFillColor(const QColor &fillColor);
        QColor getFillColor() const;

    private slots:
        void copy();
        void paste();

    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;

        QString name;
        float posx;
        float posy;
        float width;
        float height;
        int angle;
        bool lock;
        QColor lineColor;
        int lineWidth;
        bool fill;
        QColor fillColor;
    };
}
#endif // OBJECTVIEW_H
