#include "customcheckbox.h"
#include <QDebug>
#include <QMetaMethod>

CustomCheckBox::CustomCheckBox(QString text, QWidget *parent) :
    QCheckBox(text, parent)
{
    qDebug() << metaObject()->className() << "methods list:";
    for(int i = metaObject()->methodOffset(); i < metaObject()->methodCount(); i++)
    {
        qDebug() << metaObject()->method(i).typeName()
                 << QString::fromLatin1(metaObject()->method(i).methodSignature()).toStdString().c_str();
    }
}

void CustomCheckBox::setState(Qt::CheckState state)
{
    setCheckState(state);
}

Qt::CheckState CustomCheckBox::checkstate()
{
    return checkState();
}

CustomCheckBox::~CustomCheckBox()
{

}
