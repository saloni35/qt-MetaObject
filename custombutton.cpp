#include "custombutton.h"
#include <QDebug>
#include <QMetaMethod>

CustomButton::CustomButton(QString text, QWidget *parent) :
    QPushButton(text, parent)
{
    qDebug() << metaObject()->className() << "methods list:";
    for(int i = metaObject()->methodOffset(); i < metaObject()->methodCount(); i++)
    {
        qDebug() << metaObject()->method(i).typeName()
                 << QString::fromLatin1(metaObject()->method(i).methodSignature()).toStdString().c_str();
    }
}

CustomButton * CustomButton::setButtonColor(QColor color)
{
     QPalette p = palette();
     p.setColor(backgroundRole(), color);
     setAutoFillBackground(true);
     setPalette(p);
     update();
}


void CustomButton::on_Button1_clicked()
{
    qDebug() << this->objectName() << "clicked";
}

CustomButton::~CustomButton()
{
    delete this;
}


