#include "objectview.h"

namespace trei {
    ObjectView::ObjectView() {

    }

    ObjectView::ObjectView(const QString &name, float posx, float posy, float width, float height, int linewidth)
        :name(name), posx(posx), posy(posy), width(width), height(height), linewidth(linewidth)
    {

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

    void ObjectView::setLinewidth(int linewidth)
    {
        this->linewidth = linewidth;
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
