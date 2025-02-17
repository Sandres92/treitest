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

        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY onNameChanged)
        Q_PROPERTY(double posx READ getPosx WRITE setPosx NOTIFY onPosxChanged)
        Q_PROPERTY(double posy READ getPosy WRITE setPosy NOTIFY onPosyChanged)
        Q_PROPERTY(double width READ getWidth WRITE setWidth)
        Q_PROPERTY(double height READ getHeight WRITE setHeight)
        Q_PROPERTY(int angle READ getAngle WRITE setAngle)
        Q_PROPERTY(bool lock READ getLock WRITE setLock)
        Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
        Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth)
        Q_PROPERTY(bool fill READ getFill WRITE setFill)
        Q_PROPERTY(QColor fillColor READ getFillColor WRITE setFillColor)

        //Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        //// you have to declare the notify signal
        //signals:
        //    void nameChanged(int newName);

        public:
            explicit ObjectView();
            explicit ObjectView(const QString &name);
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
            void unselect() const;

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
            void onClickObjectView(ObjectView *objectView);
            void onCopyObjectView(ObjectView *originObjectView);
            void onDuplicateObjectView(ObjectView *newObjectView);
            void onDeleteObjectView(ObjectView *newObjectView);

            void onBeginDrag(ObjectView *objectView);
            void onEndDrag(const ObjectView *objectView);

            void onNameChanged(const QString &name);
            void onPosxChanged(float posx);
            void onPosyChanged(float posy);

        protected:
            void mousePressEvent(QMouseEvent *event) override;
            void mouseMoveEvent(QMouseEvent *evt) override;
            void mouseReleaseEvent(QMouseEvent *) override;
            void contextMenuEvent(QContextMenuEvent *event) override;

            //void dragEnterEvent(QDragEnterEvent *event) override;
            //void dragMoveEvent(QDragMoveEvent *event) override;
            //void dropEvent(QDropEvent *event) override;
            //void dragLeaveEvent(QDragLeaveEvent *event) override;

            virtual void mousePressEventHandler() = 0;

            void cloneCommonField(ObjectView &clonedObjectView);
            void resizeObjectView();

            QString name = "";
            float posx = 0.f;
            float posy = 0.f;
            float width = 0.f;
            float height = 0.f;
            int angle = 0.f;
            bool lock = false;
            QColor lineColor ;
            int lineWidth = 0;
            bool fill = 0;
            QColor fillColor;

            QPoint mousePoint;
            QRubberBand* rubberBand;

        private slots:
            void copy();
            void duplicate();
            void deleteObjectView();

        private:
            void init();
            bool isDragged = false;
    };
}
#endif // OBJECTVIEW_H
