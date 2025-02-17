#ifndef OBJECTVIEWFACTORY2_H
#define OBJECTVIEWFACTORY2_H

#include <QMap>
#include "../factories/objectviewfactory.h"

namespace trei
{
    class ObjectViewFactory2
    {

    public:
        ObjectViewFactory2(const ObjectViewFactory2 &) = delete;
        ObjectViewFactory2 &operator=(const ObjectViewFactory2 &) = delete;

        ObjectViewFactory2();
        ~ObjectViewFactory2();

        static ObjectViewFactory2 &instance() {
            static ObjectViewFactory2 instance;
            return instance;
        }

        ObjectView *createObjectView(const QString &className, QXmlStreamReader &xml);
        ObjectView *createObjectView(const QString &className, float posx, float posy);

    private:
        QMap<QString, ObjectViewFactory *> factories;
    };
}
#endif // OBJECTVIEWFACTORY2_H
