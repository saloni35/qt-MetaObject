#include "messagewrapper.h"

MessageWrapper::MessageWrapper(QObject *parent) :
    QObject(parent)
{
    msg = new Message;
}

QVariant MessageWrapper::getMessage()
{
    QVariant var;
    var.setValue(*msg);
    return var;
}
