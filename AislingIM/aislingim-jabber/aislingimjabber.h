#ifndef AISLINGIMJABBER_H
#define AISLINGIMJABBER_H

#include <QtQml\qqml.h>
#include <QtQml/QQmlExtensionPlugin>

#include "hello.h"

class AislingIMJabber : public QQmlExtensionPlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface" FILE "aislingim-jabber.json")
#endif // QT_VERSION >= 0x050000

public:
    void registerTypes(const char *uri)
    {
        qmlRegisterType<Hello>(uri, 1, 0, "Hello");  // @uri AislingIMJabber
    }
};

#endif // AISLINGIMJABBER_H
