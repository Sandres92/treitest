#ifndef POLYGONVIEWFACTORY_H
#define POLYGONVIEWFACTORY_H

#include "objectviewfactory.h"

namespace trei
{
    class PolygonViewFactory: public ObjectViewFactory
    {
    public:
        ObjectView *createObjectView(QXmlStreamReader &xml) override;
        ObjectView *createObjectView(float posx, float posy) override;

    protected:
        void addAdditionalXMLElements(const ObjectView &objectView, QXmlStreamWriter &xml) const override;
    };
}
#endif // POLYGONVIEWFACTORY_H
