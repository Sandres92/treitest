#ifndef RECTANGLEVIEWFACTORY_H
#define RECTANGLEVIEWFACTORY_H

#include "objectviewfactory.h"

namespace trei
{
    class RectangleViewFactory: public ObjectViewFactory
    {
        public:
            ObjectView* createObjectView(QXmlStreamReader &xml) override;
            const QByteArray toXML() const override;
    };
}

#endif // RECTANGLEVIEWFACTORY_H
