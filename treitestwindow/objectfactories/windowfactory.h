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

        static WindowFactory &instance() {
            static WindowFactory instance;
            return instance;
        }

        Window *createWindow(const QXmlStreamReader &xml);
        Window *createWindow(int countWindows);
    };
}
#endif // WINDOWFACTORY_H
