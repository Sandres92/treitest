#include "objectview.h"
#include "QDebug"

#include <QMenu>
#include <QMouseEvent>
#include <QRect>
#include <QDebug>

namespace trei
{
    ObjectView::ObjectView()
    {
        init();
    }

    ObjectView::ObjectView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                           const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor)
        : name(name), posx(posx), posy(posy), width(width), height(height), angle(angle), lock(lock),
          lineColor(lineColor), lineWidth(lineWidth), fill(fill), fillColor(fillColor)
    {
        init();
    }

    ObjectView::ObjectView(const ObjectView &other)
        : name(other.name), posx(other.posx), posy(other.posy), width(other.width), height(other.height), angle(other.angle), lock(other.lock),
        lineColor(other.lineColor), lineWidth(other.lineWidth), fill(other.fill), fillColor(other.fillColor)
    {
        init();
    }

    void ObjectView::init()
    {
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

        move(posx, posy);
        resizeObjectView();
    }

    void ObjectView::setName(const QString &name)
    {
        this->name = name;
    }
    QString ObjectView::getName() const
    {
        return name;
    }

    void ObjectView::setPosx(float posx)
    {
        this->posx = posx;
        move(posx, this->posy);
        emit onPosyChanged(posx);
    }
    float ObjectView::getPosx() const
    {
        return posx;
    }

    void ObjectView::setPosy(float posy)
    {
        this->posy = posy;
        move(this->posx, posy);        
        emit onPosxChanged(posy);
    }
    void ObjectView::setPos(float posx, float posy)
    {
        this->posx = posx;
        this->posy = posy;
        move(posx, posy);
    }
    float ObjectView::getPosy() const
    {
        return posy;
    }

    void ObjectView::setWidth(float width)
    {
        this->width = width;
        resizeObjectView();
    }
    float ObjectView::getWidth() const
    {
        return width;
    }

    void ObjectView::setHeight(float height)
    {
        this->height = height;
        resizeObjectView();
    }
    float ObjectView::getHeight() const
    {
        return height;
    }

    void ObjectView::setSize(float width, float height)
    {
        this->width = width;
        this->height = height;
        resizeObjectView();
    }

    void ObjectView::resizeObjectView()
    {        
        rubberBand->setGeometry(QRect(-lineWidth/2.f, -lineWidth/2.f, width + lineWidth, height + lineWidth));
        resize(width + lineWidth, height + lineWidth);
    }

    void ObjectView::setAngle(int angle)
    {
        this->angle = angle;
    }
    int ObjectView::getAngle() const
    {
        return angle;
    }

    void ObjectView::setLock(bool lock)
    {
        this->lock = lock;
    }
    bool ObjectView::getLock() const
    {
        return lock;
    }

    void ObjectView::setLineColor(const QColor &lineColor)
    {
        this->lineColor = lineColor;
        repaint();
    }
    QColor ObjectView::getLineColor() const
    {
        return lineColor;
    }

    void ObjectView::setLineWidth(int lineWidth)
    {
        this->lineWidth = lineWidth;
        resizeObjectView();
        repaint();
    }
    int ObjectView::getLineWidth() const
    {
        return lineWidth;
    }

    void ObjectView::setFill(bool fill)
    {
        this->fill = fill;
        repaint();
    }
    bool ObjectView::getFill() const
    {
        return fill;
    }

    void ObjectView::setFillColor(const QColor &fillColor)
    {
        this->fillColor = fillColor;
        repaint();
    }
    QColor ObjectView::getFillColor() const
    {
        return fillColor;
    }

    void ObjectView::contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu menu(this);
        menu.addAction("Копировать", this, &ObjectView::copy);
        menu.addAction("Дублировать", this, &ObjectView::duplicate);
        menu.addSeparator();
        menu.addAction("Удалить", this, &ObjectView::deleteObjectView);

        menu.exec(event->globalPos());
    }

    void ObjectView::copy()
    {
        emit onCopyObjectView(this);
    }

    void ObjectView::duplicate()
    {
        emit onDuplicateObjectView(this);
    }

    void ObjectView::deleteObjectView()
    {
        emit onDeleteObjectView(this);
    }

    void ObjectView::mousePressEvent(QMouseEvent *event)
    {
        mousePoint = event->globalPos();
        mousePressEventHandler();

        rubberBand->show();
        isDragged = false;

        emit onClickObjectView(this);
    }

    void ObjectView::mouseMoveEvent(QMouseEvent *event)
    {
        if(lock)
        {
            return;
        }
        const QPointF delta = event->globalPos() - mousePoint;

        if(delta.x()*delta.x() < 9 &&
            delta.y()*delta.y() < 9)
        {
            return;
        }

        if(!isDragged)
        {
            isDragged = true;
            emit onBeginDrag(this);
        }

        move(x()+delta.x(), y()+delta.y());

        posx += delta.x();
        posy += delta.y();

        mousePoint = event->globalPos();
    }

    void ObjectView::mouseReleaseEvent(QMouseEvent *)
    {
        if(isDragged)
        {
            isDragged = false;
            emit onEndDrag(this);
        }
    }

    //void ObjectView::dragEnterEvent(QDragEnterEvent *event)
    //{
    //    qDebug() << "dragEnterEvent";
    //}
    //void ObjectView::dragMoveEvent(QDragMoveEvent *event)
    //{
    //    qDebug() << "dragMoveEvent";
    //}
    //void ObjectView::dropEvent(QDropEvent *event)
    //{
    //    qDebug() << "dropEvent";
    //}
    //void ObjectView::dragLeaveEvent(QDragLeaveEvent *event)
    //{
    //    qDebug() << "dragLeaveEvent";
    //}

    void ObjectView::select()
    {
        rubberBand->show();
    }

    void ObjectView::unselect() const
    {
        rubberBand->hide();
    }
}
