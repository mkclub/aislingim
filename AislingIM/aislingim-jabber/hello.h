#ifndef HELLO_H
#define HELLO_H

#endif // HELLO_H

#include <QObject>
#include <QString>
#include "../aislingim-libjingle/HelloWorld.h"

class Hello: public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QString SayHello(const QString& name) {
        return QString(hello(name.toStdString()).c_str());
    }
};
