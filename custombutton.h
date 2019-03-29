#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CustomButton(QString text, QWidget *parent = 0);
    Q_INVOKABLE ~CustomButton();

public slots:
    void on_Button1_clicked();

private:
    Q_INVOKABLE CustomButton * setButtonColor(QColor);
};

#endif // CUSTOMBUTTON_H
