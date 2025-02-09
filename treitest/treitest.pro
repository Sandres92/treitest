QT = core gui widgets

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        engine.cpp \
        factories/ellipseviewfactory.cpp \
        factories/objectviewfactories.cpp \
        factories/objectviewfactory.cpp \
        factories/polygonviewfactory.cpp \
        factories/rectangleviewfactory.cpp \
        objects/objectview.cpp \
        objects/ellipseview.cpp \
        objects/polygonview.cpp \
        objects/rectangleview.cpp \
        window.cpp \
        main.cpp \
        xmlparser.cpp

HEADERS += \
            engine.h \
            factories/ellipseviewfactory.h \
            factories/objectviewfactories.h \
            factories/objectviewfactory.h \
            factories/polygonviewfactory.h \
            factories/rectangleviewfactory.h \
            objects/objectview.h \
            objects/ellipseview.h \
            objects/polygonview.h \
            objects/rectangleview.h \
            utility/convector.h \
            window.h \
            xmlparser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources/figure.xml \
            resources/figure_copy.xml \
            resources/figure_copy_copy.xml
