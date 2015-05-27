#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    offset_x = 5;
    offset_y = 5;

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);//无边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);//背景透明（需要上一行配合）
    timer = new QTimer(this);//控制刷新定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));

    timer->start(27);

}

void MainWindow::Update()
{
    int mouse_x = QCursor::pos().x();
    int mouse_y = QCursor::pos().y();

    int canvas_x = this->pos().x();
    int canvas_y = this->pos().y();

    int x = mouse_x - canvas_x - 5 + offset_x;// 减5由鼠标图片左边距而定
    int y = mouse_y - canvas_y - 5 + offset_y;// 减5由鼠标图片上边距而定
    ui->cursorLable->move(x,y);

    ui->label->setText(QString::number(mouse_x)+"-"+QString::number(x));
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}
