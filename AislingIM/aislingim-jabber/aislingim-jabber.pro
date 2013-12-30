#-------------------------------------------------
#
# Project created by QtCreator 2013-12-30T15:39:33
#
#-------------------------------------------------

QT       += qml qml-private gui gui-private quick

TARGET = aislingim-jabber
TEMPLATE = lib
CONFIG += qt plugin

SOURCES += aislingimjabber.cpp

HEADERS += aislingimjabber.h
OTHER_FILES += aislingim-jabber.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
