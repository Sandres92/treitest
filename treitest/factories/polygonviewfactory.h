#ifndef POLYGONVIEWFACTORY_H
#define POLYGONVIEWFACTORY_H

#include "objectviewfactory.h"

namespace trei
{
    class PolygonViewFactory: public ObjectViewFactory
    {
        public:
            ObjectView *createObjectView(QXmlStreamReader &xml) override;
            const QByteArray toXML() const override;
    };
}
#endif // POLYGONVIEWFACTORY_H
