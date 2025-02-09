#ifndef ELLIPSEVIEWFACTORY_H
#define ELLIPSEVIEWFACTORY_H

#include "objectviewfactory.h"

namespace trei
{
    class EllipseViewFactory: public ObjectViewFactory
    {
        public:
            ObjectView* createObjectView(QXmlStreamReader &xml) override;
            const QByteArray toXML() const override;
    };
}
#endif // ELLIPSEVIEWFACTORY_H
