#include "rectangleviewfactory.h"

#include "objects/rectangleview.h"

namespace trei
{
    ObjectView *RectangleViewFactory::createObjectView(QXmlStreamReader &xml)
    {
        return createCommonObjectView<RectangleView>(xml);
    }
}
