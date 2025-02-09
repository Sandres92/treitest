#ifndef OBJECTVIEWFACTORIES_H
#define OBJECTVIEWFACTORIES_H

#include <QString>
#include "factories/objectviewfactory.h"
#include "window.h"

namespace trei {
    class ObjectViewFactories
    {
        public:
            ObjectViewFactories();
            ~ObjectViewFactories();

            Window *createWindow(const QXmlStreamReader &xml);
            ObjectView *createObjectView(const QString &className, QXmlStreamReader &xml);

        private:
            QMap<QString, ObjectViewFactory*> factories;
    };
}
#endif // OBJECTVIEWFACTORIES_H
