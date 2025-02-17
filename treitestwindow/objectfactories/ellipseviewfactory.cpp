#include "ellipseviewfactory.h"

#include "objects/ellipseview.h"

namespace trei
{
    ObjectView *EllipseViewFactory::createObjectView(QXmlStreamReader &xml)
    {
        EllipseView *ellipseView = createCommonObjectView<EllipseView>(xml);
        return ellipseView;
    }

    ObjectView *EllipseViewFactory::createObjectView(float posx, float posy)
    {
        EllipseView *ellipseView = createCommonObjectView<EllipseView>("Эллипс", posx, posy);
        return ellipseView;
    }
}
