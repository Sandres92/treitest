#include <QApplication>

#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    trei::Engine *engine = new trei::Engine();
    engine->init();

    return app.exec();
}
