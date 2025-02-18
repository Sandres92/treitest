#ifndef POLYGONVIEWFACTORY_H
#define POLYGONVIEWFACTORY_H

#include "objectviewfactory.h"

namespace trei
{
    class PolygonViewFactory: public ObjectViewFactory
    {
    public:
        ObjectView *createObjectView() override;
        ObjectView *createObjectView(QXmlStreamReader &xml) override;
        ObjectView *createObjectView(float posx, float posy) override;
    };
}
#endif // POLYGONVIEWFACTORY_H
