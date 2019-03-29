#ifndef CUSTOMCOLORDIALOG_H
#define CUSTOMCOLORDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVariant>
#include <QLabel>

class CustomColorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomColorDialog(QWidget *parent = 0);
    QPushButton* button_select;
    QColor color;

signals:

private slots:
    void checkInputs();
    void setButtonText(QAction *);
    void setColor(QColor);
    void setValues();

private:
    Q_INVOKABLE void addButtonActions(QList<QAction *>);
    Q_INVOKABLE QVariant getValues();
    QLabel*             m_label;
    QPushButton*        color_select;
    QDialogButtonBox*   box;
    QVariant            var;
};

#endif // CUSTOMCOLORDIALOG_H
