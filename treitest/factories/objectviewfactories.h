#ifndef OBJECTVIEWFACTORIES_H
#define OBJECTVIEWFACTORIES_H

#include <QString>
#include "objectviewfactory.h"
#include "windowfactory.h"

namespace trei {
    class ObjectViewFactories
    {
        public:
            ObjectViewFactories();
            ~ObjectViewFactories();

            Window *createWindow(const QXmlStreamReader &xml);
            ObjectView *createObjectView(const QString &className, QXmlStreamReader &xml);

        private:
            WindowFactory windowFactory;
            QMap<QString, ObjectViewFactory*> factories;

    };
}
#endif // OBJECTVIEWFACTORIES_H
