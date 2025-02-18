QT       += core gui concurrent

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
    xmlparser.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#RESOURCES += \
#            resources/window_description.xml \
#            resources/window_description_origin.xml

INCLUDEPATH += $$PWD/libs/include

win32 {
    LIBS += -L$$PWD/libs -lQtSolutions_PropertyBrowser-head
}
unix {
    LIBS += -L$$PWD/libs -lQtSolutions_PropertyBrowser-head
}

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/release
win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/debug
unix:CONFIG(release, debug|release): DESTDIR = $$PWD/bin

win32 {
    CONFIG += copy_dll
    copy_dll.commands = $$QMAKE_COPY $$PWD/libs/QtSolutions_PropertyBrowser-head.dll $$DESTDIR/
    QMAKE_EXTRA_COMPILERS += copy_dll
}

unix {
    CONFIG += copy_so
    copy_so.commands = cp $$PWD/libs/libQtSolutions_PropertyBrowser-head.so $$DESTDIR/
    QMAKE_EXTRA_COMPILERS += copy_so
}

DISTFILES += \
    resources/window_description.xml \
    resources/window_description_origin.xml

CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/

exists($$OUT_PWD/window_description.xml) {
    message("Файл уже существует: $$XML_DEST")
} else {
    message("Копирование файла: $$XML_SOURCE -> $$XML_DEST")

    #copy_to_build.path = $$DESTDIR
    #copy_to_build.files = $$XML_SOURCE
    #INSTALLS += copy_to_build

    copy_to_build.path = $$DESTDIR
    copy_to_build.files = resources/window_description.xml

    INSTALLS += \
        copy_to_build
}
