#ifndef AISLINGIMJABBER_H
#define AISLINGIMJABBER_H

#include <QtQml\qqml.h>
#include <QtQml/QQmlExtensionPlugin>

class AislingIMJabber : public QQmlExtensionPlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QScriptExtensionInterface" FILE "aislingim-jabber.json")
#endif // QT_VERSION >= 0x050000

public:
    void registerTypes(const char *uri)
    {
        // TODO
        //qmlRegisterType<MyModel>(uri, 1, 0, "MyModel");
    }
};

#endif // AISLINGIMJABBER_H
