#ifndef CUSTOMRECTANGLE_H
#define CUSTOMRECTANGLE_H

#include <QFrame>
#include "custombutton.h"
#include "customcheckbox.h"

class CustomRectangle : public QFrame
{
    Q_OBJECT
public:
    explicit CustomRectangle(QWidget *parent = 0);

signals:

public slots:
    void delete_button();

private:
    Q_INVOKABLE void create_button();
    Q_INVOKABLE void change_background();
    Q_INVOKABLE void create_checkbox();
    Q_INVOKABLE void change_checkstate();
    Q_INVOKABLE void prepare_submenu();
    Q_INVOKABLE CustomButton * getButtonChildAt(int);
    Q_INVOKABLE CustomCheckBox * getCheckBoxChildAt(int);
    Q_INVOKABLE void open_bckdialog();
    CustomButton*       customize_Button;
    QPushButton*        customize_checkbox;
    int but_cnt = 0;
    int chkbx_cnt = 0;
};

#endif // CUSTOMRECTANGLE_H
