#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customrectangle.h"
#include <QDebug>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setGeometry(QApplication::desktop()->availableGeometry());

    m_button = new QPushButton("Click to Create Rectangle", this);
    m_button->setGeometry(0, 0, 200, 30);

    m_area = new QScrollArea(this);
    m_area->setGeometry(10, m_button->height() + 10, width() - 20, height() - 100);
    m_area->setWidgetResizable(true);

    QWidget *widget = new QWidget();
    m_area->setWidget( widget );

    m_layout = new QVBoxLayout(m_area);
    widget->setLayout(m_layout);

    QObject::connect(m_button, &QPushButton::clicked, this, &MainWindow::createRectangle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createRectangle()
{
    CustomRectangle* custom_rect;
    custom_rect = new CustomRectangle();    

    custom_rect->setMinimumHeight(200);
    custom_rect->setMaximumHeight(200);
    custom_rect->setMinimumWidth(m_area->width() - 20);

    m_layout->addWidget(custom_rect);  

    rect_count++;

    /*QString name = "Button";
    name.append(QString::number(but_count));

    CustomButton* custom_button;
    custom_button = qobject_cast<CustomButton *>(m_button->metaObject()->newInstance(Q_ARG(QString, name), Q_ARG(QWidget *, this)));

    CustomButton* action_button;
    action_button = qobject_cast<CustomButton *>(m_button->metaObject()->newInstance(Q_ARG(QString, "Click to change background"), Q_ARG(QWidget *, this)));

    //QObject::connect(action_button, &QPushButton::clicked, custom_button, &CustomButton::setButtonColor);

    custom_button->setGeometry(0, m_button->height() + 10 + 10 * but_count + 30 * but_count, 100, 30);
    custom_button->show();

    action_button->setGeometry(105, m_button->height() + 10 + 10 * but_count + 30 * but_count, 200, 30);
    action_button->show();

    but_count++;

    QColor col(100, 150, 200);
    QMetaObject::invokeMethod(custom_button, "setButtonColor", Q_ARG(QColor, col));

    qDebug() << custom_button->metaObject()->className();
    for(int i = custom_button->metaObject()->methodOffset(); i < custom_button->metaObject()->methodCount(); i++)
    {
        custom_button->metaObject()->method(i).invoke(custom_button, Q_ARG(QColor, col));
        qDebug() << QString::fromLatin1(custom_button->metaObject()->method(i).methodSignature());
        qDebug() << QString::fromLatin1(custom_button->metaObject()->method(i).typeName());
    }*/
}
