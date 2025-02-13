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
        resize(width + lineWidth, height + lineWidth);
        move(posx, posy);

        init();
    }

    ObjectView::ObjectView(const ObjectView &other)
        : name(other.name), posx(other.posx), posy(other.posy), width(other.width), height(other.height), angle(other.angle), lock(other.lock),
        lineColor(other.lineColor), lineWidth(other.lineWidth), fill(other.fill), fillColor(other.fillColor)
    {
        resize(width + lineWidth, height + lineWidth);
        move(posx, posy);

        init();
    }

    void ObjectView::init()
    {
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(-1.f, -1.f, width + 1.f, height + 1.f));
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
    }
    float ObjectView::getPosx() const
    {
        return posx;
    }

    void ObjectView::setPosy(float posy)
    {
        this->posy = posy;
        move(this->posx, posy);
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
    }
    float ObjectView::getWidth() const
    {
        return width;
    }

    void ObjectView::setHeight(float height)
    {
        this->height = height;
    }
    float ObjectView::getHeight() const
    {
        return height;
    }

    void ObjectView::setSize(float width, float height)
    {
        this->width = width;
        this->height = height;
        resize(width, height);
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
    }
    QColor ObjectView::getLineColor() const
    {
        return lineColor;
    }

    void ObjectView::setLineWidth(int lineWidth)
    {
        this->lineWidth = lineWidth;
    }
    int ObjectView::getLineWidth() const
    {
        return lineWidth;
    }

    void ObjectView::setFill(bool fill)
    {
        this->fill = fill;
    }
    bool ObjectView::getFill() const
    {
        return fill;
    }

    void ObjectView::setFillColor(const QColor &fillColor)
    {
        this->fillColor = fillColor;
    }
    QColor ObjectView::getFillColor() const
    {
        return fillColor;
    }

    void ObjectView::contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu menu(this);
        menu.addAction("Копировать", this, &ObjectView::copy);
        menu.addSeparator();
        menu.addAction("Дублировать", this, &ObjectView::duplicate);

        menu.exec(event->globalPos());
    }

    void ObjectView::copy()
    {
        qDebug() << "copy";
        emit onObjectViewCopy(this);
    }

    void ObjectView::duplicate()
    {

        emit onObjectViewDuplicate(this);
    }

    void ObjectView::mousePressEvent(QMouseEvent *event)
    {
        mousePoint = event->globalPos();
        mousePressEventHandler();

        rubberBand->show();
        emit onObjectViewClick(this);

        raise();
    }

    void ObjectView::mouseMoveEvent(QMouseEvent *event)
    {
        const QPointF delta = event->globalPos() - mousePoint;
        move(x()+delta.x(), y()+delta.y());

        posx += delta.x();
        posy += delta.y();

        mousePoint = event->globalPos();
    }

    void ObjectView::mouseReleaseEvent(QMouseEvent *)
    {
        qDebug() << "mouseReleaseEvent";
    }

    void ObjectView::select()
    {
        rubberBand->show();
    }

    void ObjectView::unselect()
    {
        rubberBand->hide();
    }
}
