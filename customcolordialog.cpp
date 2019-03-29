#include "customcolordialog.h"
#include <QDebug>
#include <QMenu>
#include <QMessageBox>
#include <QAction>
#include <QColorDialog>
#include "messagewrapper.h"
#include "message.h"

CustomColorDialog::CustomColorDialog(QWidget *parent) :
    QDialog(parent)
{    
    button_select = new QPushButton("Select Button", this);
    button_select->setGeometry(10, 10, 150, 40);

    box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setGeometry(geometry().width() - 40, geometry().height() - 40, 100, 40);
    box->show();

    m_label = new QLabel("Select Colour:", this);
    m_label->setGeometry(10, 60, 100, 40);
    m_label->show();

    color_select = new QPushButton(this);
    color_select->setGeometry(110, 70, 20, 20);
    color_select->setStyleSheet("background-color: rgb(255,255,0);");

    QColorDialog* colDialog = new QColorDialog(this);

    QObject::connect(color_select, &QPushButton::clicked, colDialog, &QDialog::open);
    QObject::connect(colDialog, &QColorDialog::colorSelected, this, &CustomColorDialog::setColor);
    QObject::connect(box->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &CustomColorDialog::checkInputs);
    QObject::connect(box->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &QDialog::reject);
    QObject::connect(this, &QDialog::accepted, this, &CustomColorDialog::setValues);
}

void CustomColorDialog::addButtonActions(QList<QAction *> actions)
{
    if(actions.size() > 0)
    {
        QMenu * menu = new QMenu;
        menu->addActions(actions);
        button_select->setMenu(menu);
        QObject::connect(menu, &QMenu::triggered, this, &CustomColorDialog::setButtonText);
    }
}

void CustomColorDialog::checkInputs()
{
    if(button_select->text() == "Select Button")
    {
        QMessageBox alert;
        MessageWrapper* msgw = new MessageWrapper;
        Message msg;
        QVariant msgvariant;
        QMetaObject::invokeMethod(msgw, "getMessage", Q_RETURN_ARG(QVariant, msgvariant));
        msg = msgvariant.value<Message>();
        alert.setText(msg.body());
        alert.exec();
    }
    else if(!color.isValid())
    {
        QMessageBox alert;
        alert.setText("Please select Color");
        alert.exec();
    }
    else
        accept();
}

void CustomColorDialog::setButtonText(QAction * action)
{
    button_select->setText(action->text());
}

void CustomColorDialog::setColor(QColor col)
{
    QString qss = QString("background-color: rgb(%1 , %2, %3);").arg(QString::number(col.red()),
                                                                  QString::number(col.green()), QString::number(col.blue()));
    color_select->setStyleSheet(qss);
    color = col;
}

void CustomColorDialog::setValues()
{
    var.setValue(this);
}
QVariant CustomColorDialog::getValues()
{
    return var;
}
