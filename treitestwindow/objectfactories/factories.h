#ifndef FACTORIES_H
#define FACTORIES_H

#include <QString>
#include "objectviewfactory.h"
#include "windowfactory.h"

namespace trei
{
    class Factories
    {
    public:
        Factories() = default;
        ~Factories() = default;

        Window *createWindow(const QXmlStreamReader &xml);
        ObjectView *createObjectView(const QString &className, QXmlStreamReader &xml);
    };
}
#endif // FACTORIES_H
