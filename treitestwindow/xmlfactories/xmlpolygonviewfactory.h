#ifndef XMLPOLYGONVIEWFACTORY_H
#define XMLPOLYGONVIEWFACTORY_H

#include "objects/objectview.h"
#include <QXmlStreamWriter>
#include "xmlobjectviewfactory.h"

namespace trei
{
    class XMLPolygonViewFactory : public XMLObjectViewFactory
    {
        public:
            XMLPolygonViewFactory();

        protected:
            void addAdditionalXMLElements(const ObjectView &objectView, QXmlStreamWriter &xml) const override;
    };
}
#endif // XMLPOLYGONVIEWFACTORY_H
