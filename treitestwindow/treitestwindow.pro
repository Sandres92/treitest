QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    objectfactories/factories.cpp \
    objectfactories/objectviewfactories.cpp \
    main.cpp \
    mainwindow.cpp \
    engine.cpp \
    objectfactories/ellipseviewfactory.cpp \
    objectfactories/objectviewfactory.cpp \
    objectfactories/polygonviewfactory.cpp \
    objectfactories/rectangleviewfactory.cpp \
    objectfactories/windowfactory.cpp \
    objects/objectview.cpp \
    objects/ellipseview.cpp \
    objects/polygonview.cpp \
    objects/rectangleview.cpp \
    propertybrowserdockwidget.cpp \
    window.cpp \
    xmlfactories/xmlellipseviewfactory.cpp \
    xmlfactories/xmlfactories.cpp \
    xmlfactories/xmlobjectviewfactories.cpp \
    xmlfactories/xmlobjectviewfactory.cpp \
    xmlfactories/xmlpolygonviewfactory.cpp \
    xmlfactories/xmlrectangleviewfactory.cpp \
    xmlfactories/xmlwindowfactory.cpp \
    xmlfactory.cpp \
    xmlparser.cpp

HEADERS += \
    objectfactories/factories.h \
    objectfactories/objectviewfactories.h \
    mainwindow.h \
    engine.h \
    objectfactories/ellipseviewfactory.h \
    objectfactories/objectviewfactory.h \
    objectfactories/polygonviewfactory.h \
    objectfactories/rectangleviewfactory.h \
    objectfactories/windowfactory.h \
    objects/objectview.h \
    objects/ellipseview.h \
    objects/polygonview.h \
    objects/rectangleview.h \
    propertybrowserdockwidget.h \
    utility/convector.h \
    window.h \
    xmlfactories/xmlellipseviewfactory.h \
    xmlfactories/xmlfactories.h \
    xmlfactories/xmlobjectviewfactories.h \
    xmlfactories/xmlobjectviewfactory.h \
    xmlfactories/xmlpolygonviewfactory.h \
    xmlfactories/xmlrectangleviewfactory.h \
    xmlfactories/xmlwindowfactory.h \
    xmlfactory.h \
    xmlparser.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources/figure.xml \
            resources/figure_copy.xml \
            resources/figure_copy_copy.xml

INCLUDEPATH += $$PWD/libs/include
LIBS += -L$$PWD/libs -lQtSolutions_PropertyBrowser-head

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/release
win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/debug

win32 {
    CONFIG += copy_dll
    copy_dll.commands = $$QMAKE_COPY $$PWD/libs/QtSolutions_PropertyBrowser-head.dll $$DESTDIR/
    QMAKE_EXTRA_COMPILERS += copy_dll
}
