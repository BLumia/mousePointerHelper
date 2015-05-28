#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void doHideOptBox(bool doHide);

private:
    Ui::MainWindow *ui;

    QTimer * timer;
    int offset_x;
    int offset_y;
    bool clickOnFrame;
    bool drawCanDragCover;//绘制可被拖拽的覆盖
    QPoint drag_pos;//用于窗口拖动，存储鼠标坐标

    //动画
    QPropertyAnimation *optSlideAnimation;


private slots:
    void Update();

    void on_xoffsetSpinBox_valueChanged(int arg1);
    void on_yoffsetSpinBox_valueChanged(int arg1);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void on_moveCanvasCheckr_clicked(bool checked);

    void on_exitBtn_clicked();

    void on_hideOptBoxBtn_clicked();

    void on_showOptBoxBtn_clicked();

    void on_canvasSizeBtn_clicked();

protected:
    void paintEvent(QPaintEvent *);

};

#endif // MAINWINDOW_H
