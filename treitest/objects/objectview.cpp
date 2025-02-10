#include "objectview.h"
#include "QDebug"

namespace trei
{
    ObjectView::ObjectView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                           const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor)
        : name(name), posx(posx), posy(posy), width(width), height(height), angle(angle), lock(lock),
          lineColor(lineColor), lineWidth(lineWidth), fill(fill), fillColor(fillColor)
    {
        resize(width + lineWidth, height + lineWidth);
        move(posx, posy);
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
}
