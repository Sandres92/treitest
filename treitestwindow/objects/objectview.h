#ifndef OBJECTVIEW_H
#define OBJECTVIEW_H

#include <QPaintDevice>
#include <QWidget>
#include <QString>
#include <QColor>
#include <QRubberBand>

namespace trei
{
    class ObjectView: public QWidget
    {
        Q_OBJECT

    public:
        explicit ObjectView();
        explicit ObjectView(const QString &name, float posx, float posy, float width, float height,
                            int angle, bool lock, const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor);
        explicit ObjectView(const ObjectView &other);

        virtual ~ObjectView() = default;

        virtual ObjectView *clone() = 0;

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

        void select();
        void unselect();

        friend QDataStream &operator<<(QDataStream &out, ObjectView &objectView)
        {
            out << objectView.name << objectView.posx << objectView.posy << objectView.width <<
                objectView.height << objectView.angle << objectView.lock << objectView.lineColor <<
                objectView.lineWidth << objectView.fill << objectView.fillColor;
            return out;
        }

        friend QDataStream &operator>>(QDataStream &in, ObjectView &objectView)
        {
            in >> objectView.name >> objectView.posx >> objectView.posy >> objectView.width >>
                objectView.height >> objectView.angle >> objectView.lock >> objectView.lineColor >>
                objectView.lineWidth >> objectView.fill >> objectView.fillColor;
            return in;
        }

    signals:
        void onObjectViewClick(ObjectView *objectView);
        void onObjectViewCopy(ObjectView *originObjectView);
        void onObjectViewDuplicate(ObjectView *newObjectView);

    protected:
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *evt) override;
        void mouseReleaseEvent(QMouseEvent *) override;
        void contextMenuEvent(QContextMenuEvent *event) override;

        virtual void mousePressEventHandler() = 0;

        void cloneCommonField(ObjectView &clonedObjectView);

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

        QPoint mousePoint;
        QRubberBand* rubberBand;

    private slots:
        void copy();
        void duplicate();

    private:
        void init();
    };
}
#endif // OBJECTVIEW_H
