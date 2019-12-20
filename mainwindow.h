#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>
#include <board.h>
#include "menu.h"
#include<QWidget>
#include <QPushButton>
class QLCDNumber;
class QPaintEvent;
class menu;
QT_BEGIN_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool ispause;//判断是否暂停状态
    QTimer *timer ,*t; //定时器
    Board *board;//游戏所用地图类
    int level;    //关卡等级
    int pictureID;  //背景图片

    MainWindow(Board *, int level, int, QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);//绘制界面
    void keyPressEvent(QKeyEvent *);//键盘处理事件

    void slowdown();   //减速道具
    void del();        //清除两行道具
    void clearall();   //清屏道具

    //2个按钮
    QPushButton *quitButton;   //退出游戏指针
    QPushButton *stopButton;   //暂停游戏指针

signals:

public slots:
    void timerEvent();
    void back();     //退出游戏
    void stop();     //暂停游戏
    void timerout();

private:
    menu *w;
    int timeoutTime(){return level*200;}
};

#endif // MAINWINDOW_H

