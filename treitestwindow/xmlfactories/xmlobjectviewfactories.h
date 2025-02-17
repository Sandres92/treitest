#ifndef XMLOBJECTVIEWFACTORIES_H
#define XMLOBJECTVIEWFACTORIES_H

#include <QMap>
#include <QString>
#include "xmlobjectviewfactory.h"

namespace trei
{
    class XMLObjectViewFactories
    {
        public:
            XMLObjectViewFactories();

            static XMLObjectViewFactories &instance() {
                static XMLObjectViewFactories instance;
                return instance;
            }

        private:
            QMap<QString, XMLObjectViewFactory *> factories;
    };
}
#endif // XMLOBJECTVIEWFACTORIES_H
