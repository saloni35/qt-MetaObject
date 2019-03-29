#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSplitter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void createRectangle();

private:
    Ui::MainWindow*     ui;
    QPushButton*        m_button;
    QScrollArea*        m_area;
    QVBoxLayout*        m_layout;
    QSplitter*          m_splitter;
    int                 rect_count = 0;
};

#endif // MAINWINDOW_H
