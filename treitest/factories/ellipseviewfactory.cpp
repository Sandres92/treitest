#include "ellipseviewfactory.h"

#include "objects/ellipseview.h"

namespace trei
{
    ObjectView* EllipseViewFactory::createObjectView(QXmlStreamReader &xml)
    {
        EllipseView* ellipseView = createCommonObjectView<EllipseView>(xml);
        return ellipseView;
    }

    const QByteArray EllipseViewFactory::toXML() const
    {
        return nullptr;
    }
}
