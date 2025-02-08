#ifndef ENGINE_H
#define ENGINE_H

#include <QDebug>

#include <QWidget>
#include <QWindow>

#include "window.h"
#include "objects/rectangleview.h"
#include "objects/ellipseview.h"
#include "objects/polygonview.h"

namespace trei {
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void init();

    private:
        void parseWindow();
        Window * createWindow(const QXmlStreamReader &xml);
        RectangleView *createRectangleView(const QXmlStreamReader &xml);
        EllipseView *createEllipseView(const QXmlStreamReader &xml);
        PolygonView *createPolygonView(QXmlStreamReader &xml);
    };
}


#endif // ENGINE_H
