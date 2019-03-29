#include "customrectangle.h"
#include "customcheckbox.h"
#include "customcolordialog.h"
#include <QDebug>
#include <QMenu>
#include <QMetaMethod>
#include <QScrollArea>

CustomRectangle::CustomRectangle(QWidget *parent) :
    QFrame(parent)
{    
    setFrameShape(QFrame::Box);
    setLineWidth(2);    

    qDebug() << metaObject()->className() << "methods list:";
    for(int i = metaObject()->methodOffset(); i < metaObject()->methodCount(); i++)
    {
        qDebug() << metaObject()->method(i).typeName()
                 << QString::fromLatin1(metaObject()->method(i).methodSignature()).toStdString().c_str();
    }

    customize_Button = new CustomButton("Customize Button", this);
    customize_Button->setGeometry(10, 10, 200, 30);
    customize_checkbox = new QPushButton("Customize Checkbox", this);
    customize_checkbox->setGeometry(220, 10, 200, 30);

    QObject::connect(customize_checkbox, &QPushButton::pressed, this, &CustomRectangle::prepare_submenu);

    QMenu* button_menu = new QMenu;
    button_menu->addAction("Create Button", this, SLOT(create_button()));
    button_menu->addAction("Change Background", this, SLOT(open_bckdialog()));
    button_menu->addAction("Delete Button", this, SLOT(delete_button()));

    QMenu* checkbox_menu = new QMenu;
    checkbox_menu->addAction("Create Checkbox", this, SLOT(create_checkbox()));
    checkbox_menu->addAction("Change Check State", this, SLOT(change_checkstate()));

    customize_Button->setMenu(button_menu);
    customize_checkbox->setMenu(checkbox_menu);
}

void CustomRectangle::open_bckdialog()
{
    if(but_cnt > 0)
    {
        CustomColorDialog* bckcolorDialog = new CustomColorDialog;
        QList<QAction*> actList;
        for(int i = 0; i < but_cnt; i++)
        {
            QString name = customize_Button->metaObject()->className();
            name.append(QString::number(i));
            actList.append(new QAction(name, bckcolorDialog));
        }
        QMetaObject::invokeMethod(bckcolorDialog, "addButtonActions", Q_ARG(QList<QAction* >, actList));
        bckcolorDialog->open();
        QObject::connect(bckcolorDialog, &QDialog::accepted, this, &CustomRectangle::change_background);
    }
}

void CustomRectangle::create_button()
{
    QAction *act = qobject_cast<QAction *>(sender());
    if(act)
    {
        customize_Button->setText(act->text());
        CustomButton* button;
        QString name = customize_Button->metaObject()->className();
        name.append(QString::number(but_cnt));
        button = qobject_cast<CustomButton *>(customize_Button->metaObject()->newInstance(Q_ARG(QString, name), Q_ARG(QWidget *, this)));
        button->setGeometry(10, 50 + 30 * but_cnt, 150, 30);
        button->show();
        but_cnt++;
    }
}

void CustomRectangle::prepare_submenu()
{
    QList<QAction* > actList1 = customize_checkbox->menu()->actions();
    QAction* act_check = actList1.at(1);

    if(act_check)
    {
        if(chkbx_cnt > 0)
        {
            QMenu* submenu = new QMenu;
            for(int i = 0; i < chkbx_cnt; i++)
            {
                QString name = "CheckBox";
                name.append(QString::number(i));
                submenu->addAction(name, this, SLOT(change_checkstate()));
            }
            act_check->setMenu(submenu);
        }
    }
}

void CustomRectangle::change_background()
{
    QVariant var;
    QMetaObject::invokeMethod(sender(), "getValues", Q_RETURN_ARG(QVariant, var));
    CustomColorDialog* dlg = var.value<CustomColorDialog *>();
    if(dlg)
    {
        CustomButton * but;
        QString num = dlg->button_select->text().mid(12);
        QMetaObject::invokeMethod(this, "getButtonChildAt", Q_RETURN_ARG(CustomButton*, but), Q_ARG(int, num.toInt() + 1));
        QMetaObject::invokeMethod(but, "setButtonColor", Q_ARG(QColor, dlg->color));
    }
}

void CustomRectangle::create_checkbox()
{
    QAction *act = qobject_cast<QAction *>(sender());
    if(act)
    {
        customize_checkbox->setText(act->text());
        CustomCheckBox* checkbox;
        QString name = "CheckBox";
        name.append(QString::number(chkbx_cnt));
        checkbox = new CustomCheckBox(name, this);
        if(checkbox)
        {
            checkbox->setGeometry(220, 50 + 30 * chkbx_cnt, 150, 30);
            checkbox->show();
        }
        chkbx_cnt++;
    }
}

void CustomRectangle::change_checkstate()
{
    QAction *act = qobject_cast<QAction *>(sender());
    if(act)
    {
        if(act->text() == "Change Check State")
            customize_checkbox->setText(act->text());
        else
        {
            CustomCheckBox* chkbx;
            QString num = act->text().mid(8);
            QMetaObject::invokeMethod(this, "getCheckBoxChildAt", Q_RETURN_ARG(CustomCheckBox*, chkbx), Q_ARG(int, num.toInt()));
            Qt::CheckState state;
            QMetaObject::invokeMethod(chkbx, "checkstate", Q_RETURN_ARG(Qt::CheckState, state));
            if(state == Qt::Unchecked)
                QMetaObject::invokeMethod(chkbx, "setState", Q_ARG(Qt::CheckState, Qt::Checked));
            else
                QMetaObject::invokeMethod(chkbx, "setState", Q_ARG(Qt::CheckState, Qt::Unchecked));
            customize_checkbox->setText("Change Check State");
        }
    }
}

CustomButton* CustomRectangle::getButtonChildAt(int index)
{
    QList<CustomButton *> but_list;
    but_list = this->findChildren<CustomButton *>();
    return but_list.at(index);
}

CustomCheckBox* CustomRectangle::getCheckBoxChildAt(int index)
{
    QList<CustomCheckBox *> chkbx_list;
    chkbx_list = this->findChildren<CustomCheckBox *>();
    return chkbx_list.at(index);
}

void CustomRectangle::delete_button()
{
    CustomButton * b;
    QMetaObject::invokeMethod(this, "getButtonChildAt", Q_RETURN_ARG(CustomButton*, b), Q_ARG(int, 1));
    b->hide();
    b->~CustomButton();
}
