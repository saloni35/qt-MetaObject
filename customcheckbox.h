#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QCheckBox>

class CustomCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit CustomCheckBox(QString text, QWidget *parent = 0);

signals:

public slots:

private:
    Q_INVOKABLE void setState(Qt::CheckState);
    Q_INVOKABLE Qt::CheckState checkstate();
    Q_INVOKABLE ~CustomCheckBox();
};

#endif // CUSTOMCHECKBOX_H
