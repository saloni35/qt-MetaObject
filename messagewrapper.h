#ifndef MESSAGEWRAPPER_H
#define MESSAGEWRAPPER_H

#include <QObject>
#include <QVariant>
#include "message.h"

class MessageWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MessageWrapper(QObject *parent = 0);
    Q_INVOKABLE QVariant getMessage();

signals:

public slots:

private:
    Message* msg;

};

#endif // MESSAGEWRAPPER_H
