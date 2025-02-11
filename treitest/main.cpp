#include <QApplication>

#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto engine = std::make_unique<trei::Engine>();
    engine->init();

    return app.exec();
}
