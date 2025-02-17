#include "xmlobjectviewfactories.h"

#include "xmlellipseviewfactory.h"
#include "xmlrectangleviewfactory.h"
#include "xmlpolygonviewfactory.h"

namespace trei
{
    XMLObjectViewFactories::XMLObjectViewFactories()
    {
        factories["EllipseView"] = new XMLEllipseViewFactory();
        factories["RectangleView"] = new XMLRectangleViewFactory();
        factories["PolygonView"] = new XMLPolygonViewFactory();
    }
}
