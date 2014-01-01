#-------------------------------------------------
#
# Project created by QtCreator 2013-12-30T15:39:33
#
#-------------------------------------------------

QT       += core core-private qml qml-private gui gui-private quick

TARGET = aislingim-jabber
TEMPLATE = lib
CONFIG += qt plugin

SOURCES += aislingimjabber.cpp

HEADERS += aislingimjabber.h \
    hello.h
OTHER_FILES += aislingim-jabber.json

CONFIG(debug, debug|release) {
    BUILDCONFIG = "Debug"
}
CONFIG(release, debug|release) {
    BUILDCONFIG = "Release"
}

BASEDIR = "$$PWD/../../.."
DESTDIR = "$$BASEDIR/aisling-build/$$BUILDCONFIG/AislingIMJabber"

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    LIBS += "$$PWD/../aislingim-libjingle/$$BUILDCONFIG/aislingim-libjingle.lib"
}

qmldir.path = "$$DESTDIR"
qmldir.files = "qmldir" \
               "plugins.qmltypes"

libjingle.path = "$$DESTDIR/.."
libjingle.files = "$$PWD/../aislingim-libjingle/$$BUILDCONFIG/aislingim-libjingle.dll"

INSTALLS += qmldir libjingle
