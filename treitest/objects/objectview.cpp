#include "objectview.h"
#include "QDebug"

namespace trei
{
    ObjectView::ObjectView()
    {

    }

    ObjectView::ObjectView(const QString &name, float posx, float posy, float width, float height, int angle, bool lock,
                           const QColor &lineColor, int lineWidth, bool fill, const QColor &fillColor)
        :name(name), posx(posx), posy(posy), width(width), height(height), angle (angle), lock(lock),
        lineColor(lineColor), lineWidth(lineWidth), fill(fill), fillColor(fillColor)
    {
        resize(width + lineWidth, height + lineWidth);
        move(posx, posy);
    }

    ObjectView::~ObjectView() {

    }

    void ObjectView::setName(const QString &name)
    {
        this->name = name;
    }
    void ObjectView::setPosx(float posx)
    {
        this->posx = posx;
        move(posx, this->posy);
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

    void ObjectView::setWidth(float width)
    {
        this->width = width;
    }
    void ObjectView::setHeight(float height)
    {
        this->height = height;
    }
    void ObjectView::setSize(float width, float height)
    {
        this->width = width;
        this->height = height;
        resize(width, height);
    }

    void ObjectView::setLineWidth(int lineWidth)
    {
        this->lineWidth = lineWidth;
    }

    QString ObjectView::getName(QString name) const
    {
        return name;
    }

    float ObjectView::getPosx(float posx) const
    {
        return posx;
    }
    float ObjectView::getPosy(float posy) const
    {
        return posy;
    }

    float ObjectView::getWidth(float width) const
    {
        return width;
    }
    float ObjectView::getHeight(float height) const
    {
        return height;
    }
    int ObjectView::getLinewidth(int linewidth) const
    {
        return linewidth;
    }
}
