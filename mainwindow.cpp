#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    offset_x = 5;
    offset_y = 5;
    clickOnFrame = false;//是否点击到面板上
    drawCanDragCover = false;
    ui->showOptBoxBtn->setVisible(false);

    //窗口调节大小动画
    optSlideAnimation = new QPropertyAnimation(ui->optionBox, "geometry");
    optSlideAnimation->setDuration(600);
    optSlideAnimation->setEasingCurve(QEasingCurve::OutCirc);

    //this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);//无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);// | Qt::Tool
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

    ui->xposLable->setText("X ("+QString::number(mouse_x)+","+QString::number(x)+")");
    ui->yposLable->setText("Y ("+QString::number(mouse_y)+","+QString::number(y)+")");
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_xoffsetSpinBox_valueChanged(int arg1)
{
    offset_x = arg1;
}

void MainWindow::on_yoffsetSpinBox_valueChanged(int arg1)
{
    offset_y = arg1;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drag_pos = event->pos();
        clickOnFrame = true;//点击到窗口框架上才会变成true，改动之后新增功能：判断点击是否在边框右侧
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    clickOnFrame = false;//弹起鼠标按键时，恢复
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && clickOnFrame)
    {
        move(event->globalPos() - drag_pos);
        event->accept();
    }
}

void MainWindow::on_moveCanvasCheckr_clicked(bool checked)
{
    drawCanDragCover = checked;
    this->repaint();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (drawCanDragCover)
    {
        painter.setBrush(QBrush(QColor(255, 255, 255, 120)));
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, width(), height());
    }
}

void MainWindow::doHideOptBox(bool doHide)
{
    QRect startRect, endRect;
    if (doHide) {
        ui->showOptBoxBtn->setVisible(true);
        startRect = QRect(ui->optionBox->geometry().x(),
                          ui->optionBox->geometry().y(),
                          ui->optionBox->geometry().width(),
                          ui->optionBox->geometry().height());
        endRect = QRect(this->geometry().width() - ui->optionBox->geometry().width() - 15,
                        0 - ui->optionBox->geometry().height(),
                        ui->optionBox->geometry().width(),
                        ui->optionBox->geometry().height());
    } else {
        ui->showOptBoxBtn->setVisible(false);
        startRect = QRect(this->geometry().width() - ui->optionBox->geometry().width() - 15,
                          0 - ui->optionBox->geometry().height(),
                          ui->optionBox->geometry().width(),
                          ui->optionBox->geometry().height());
        endRect = QRect(this->geometry().width() - ui->optionBox->geometry().width() - 15,
                        0,
                        ui->optionBox->geometry().width(),
                        ui->optionBox->geometry().height());
    }
    optSlideAnimation->stop();
    optSlideAnimation->setStartValue(startRect);
    optSlideAnimation->setEndValue(endRect);
    optSlideAnimation->start();
    this->repaint();
}

void MainWindow::on_exitBtn_clicked()
{
    qApp->exit();//主窗口关闭后，关闭程序
}

void MainWindow::on_hideOptBoxBtn_clicked()
{
    doHideOptBox(true);
}

void MainWindow::on_showOptBoxBtn_clicked()
{
    doHideOptBox(false);
}

void MainWindow::on_canvasSizeBtn_clicked()
{
    if (!isMaximized()) {
        QWidget::showMaximized();
        this->move(0,0);
    } else
        QWidget::showNormal();

    ui->optionBox->move(QPoint(this->geometry().width() - ui->optionBox->geometry().width() - 15,15));
    ui->showOptBoxBtn->move(QPoint(this->geometry().width()- ui->showOptBoxBtn->geometry().width() - 15,0));
}
