#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "../window.h"

namespace trei
{
    class WindowFactory
    {
    public:
        WindowFactory() = default;
        ~WindowFactory() = default;

        Window *createWindow(const QXmlStreamReader &xml);
    };
}
#endif // WINDOWFACTORY_H
