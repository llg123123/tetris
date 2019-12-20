#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QMessageBox>
#include "brick.h"
#include "board.h"
#include<QWidget>
#include<QGridLayout>
#include <QIcon>
#include <QtWidgets>
using namespace std;
int slowtool=0,deltool=0,cleartool=0;
bool stisexiting=false,dtisexiting=false,ctisexiting=false;

MainWindow::MainWindow(Board *board, int level, int pictureID,  QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Car-tetris");//设置界面标题
    setWindowIcon(QIcon(":/new/prefix1/Tilte.png"));//设置界面左上角头像
    this->board = board;
    ispause = 0;
    this->level = level;
    this->pictureID = pictureID;
    //初始化定时器
    timer = new QTimer(this);
    timer->setInterval(this ->level * 200);
    //为定时器设置连接函数
    connect(timer, &QTimer::timeout, this, &MainWindow::timerEvent);

    timer->start();
    resize(15*40+3*15, 20*40+15*2);

    quitButton =  new QPushButton(this);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(back()));//返回按钮
    quitButton->setFocusPolicy(Qt::ClickFocus);//否则方向键操作无响应
    stopButton = new QPushButton(this);
    connect(stopButton,SIGNAL(clicked()),this,SLOT(stop()));//返回按钮
    stopButton->setFocusPolicy(Qt::NoFocus);//否则方向键操作无响应
}

void MainWindow::slowdown()
{
    timer->start(timeoutTime()*4);
    t=new QTimer();
    t->setInterval(20000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(timerout()));
}

void MainWindow::del()   //清除两行方块
{
    for(int j=20; j>=2; j--)
        for(int k=1; k<=10; k++)
            board->map[j][k] = board->map[j-2][k];
    board->brick->toNext();
}

void MainWindow::clearall()
{
    //这里是20注意不要越界
    for(int j=20; j>=1; j--)
        for(int k=1; k<=10; k++)
            board->map[j][k] = '#';
    board->brick->toNext();
}

void MainWindow::timerout()
{
    timer->start(level*200);
    t->stop();
}

void MainWindow::stop()
{
    timer->stop();
    ispause = 1;
    QMessageBox::information(this, tr("提醒"), tr("回到游戏"));
    ispause = 0;
    timer->start();
}

void MainWindow::back()
{
    slowtool=0,deltool=0,cleartool=0;
    stisexiting=false,dtisexiting=false,ctisexiting=false;
    w = new menu;
    w->show();
    timer->stop();
    this->close();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    int w = 40 ;//每块方块宽
    int h = 40 ;//每块方块高
    int w1 = 15 ;//边界宽
    int h1 = 15 ;//边界高
    QPainter painter(this);
    painter.setBrush(Qt::black);
    switch (this->pictureID) {
    case 1:
        painter.drawPixmap(w1,h1, w*10, h*20,  QPixmap(":/new/prefix1/background1.jpg"));
        break;
    case 2:
        painter.drawPixmap(w1,h1, w*10, h*20, QPixmap(":/new/prefix1/background2.jpg"));
        break;
    case 3:
        painter.drawPixmap(w1,h1, w*10, h*20,  QPixmap(":/new/prefix1/background3.jpg"));
        break;
    case 4:
        painter.drawPixmap(w1,h1, w*10, h*20, QPixmap(":/new/prefix1/background4.jpg"));
        break;
    case 5:
        painter.drawPixmap(w1,h1, w*10, h*20,  QPixmap(":/new/prefix1/background5.jpg"));
        break;
    default:
        break;
    }
    painter.drawPixmap(w1*2+w*10,h1, w*5, h*5, QPixmap(":/new/prefix1/background6.png"));
    painter.drawPixmap(w1*2+w*10,h1*2+h*5, w*5,this->height()-h1*3-h*5 , QPixmap(":/new/prefix1/background6.png"));


    //绘制背景方法
    for(int i=1; i<=20; i++)
    {
        for(int j=1; j<=10; j++)
        {
            char ch = board->map[i][j];
            if(ch != '#')
            {

                     if ( ch == '1')
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (1).png"));
                     else if ( ch == '2')
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (2).png"));
                     else if ( ch == '3')
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (3).png"));
                     else if ( ch == '4')
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (4).png"));
                     else if ( ch == '5')
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (5).png"));
                     else if ( ch == '6')
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (6).png"));
                     else
                         painter.drawPixmap(j*w-w+w1, i*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (7).png"));
            }
        }
    }
        painter.setBrush(Qt::darkGray);
        painter.drawRect(0, 0, w*15+3*w1, h1);//上面一行
        painter.drawRect(w1+10*w, h1+5*h, 5*w+2*w1, h1);//右边中间第一行
        painter.drawRect(w1+10*w, h1+13*h, 5*w+2*w1, h1);//右边中间第二行
        painter.drawRect(w1+10*w,17*h+2*h1,5*w+2*w1, h1);//右边中间第三行
        painter.drawRect(0, h1+h*20, 15*w+3*w1, h1);//下面一行
        painter.drawRect(0, 0,w1, 2*h1+h*20);//左边一列
        painter.drawRect(w1+w*10, 0, w1, 2*h1+h*20);//中间一列
        painter.drawRect(w1*2+w*15,0, w1, 2*h1+h*20);//右边一列

        painter.drawRect(w1*2+11.25*w,5.75*h+0.5*h1, w*2.5, h1/4.0);//道具边框
        painter.drawRect(w1*2+11.25*w,7.75*h+1.5*h1, w*2.5, h1/4.0);
        painter.drawRect(w1*2+11.25*w,9.75*h+2.5*h1, w*2.5, h1/4.0);
        painter.drawRect(w1*2+11.25*w,11.75*h+3.5*h1, w*2.5, h1/4.0);
        painter.drawRect(w1*2+11.25*w,5.75*h+0.5*h1,w1/4.0,6*h+3.25*h1);
        painter.drawRect(w1*2+13.75*w,5.75*h+0.5*h1,w1/4.0,6*h+3.25*h1);

    //绘制下一个块的提示
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int ch = board->brick->block[board->brick->nexttype][i][j];
            if(ch != '#')
            {
                 if ( ch == '1')
                    painter.drawPixmap((j+10+1)*w+w1*2, (i+1)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (1).png"));
                 else if ( ch == '2')
                    painter.drawPixmap((j+10+1)*w+w1*2, (i+1)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (2).png"));
                 else if ( ch == '3')
                    painter.drawPixmap((j+10+1)*w+w1*2, (i+1)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (3).png"));
                 else if ( ch == '4')
                    painter.drawPixmap((j+10+1)*w+w1*2, (i+1)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (4).png"));
                 else if ( ch == '5')
                    painter.drawPixmap((j+10+1)*w+w1*2, (i+1)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (5).png"));
                 else if ( ch == '6')
                    painter.drawPixmap((j+10+0.5)*w+w1*2, (i+0.5)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (6).png"));
                 else
                    painter.drawPixmap((j+10+1.5)*w+w1*2, (i+1.5)*h+h1, w, h , QPixmap(":/new/prefix1/block1 (7).png"));
            }
        }

    //绘制当前正在下落的块
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int tx = board->brick->x + i;
            int ty = board->brick->y + j;
            if(tx<1 || tx > 20 || ty < 1 || ty > 10)
                continue;
            int ch = board->brick->block[board->brick->type][i][j];
            if(ch != '#')
            {

                    if ( ch == '1')
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (1).png"));
                    else if ( ch == '2')
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (2).png"));
                    else if ( ch == '3')
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1,w, h, QPixmap(":/new/prefix1/block1 (3).png"));
                    else if ( ch == '4')
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (4).png"));
                    else if ( ch == '5')
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (5).png"));
                    else if ( ch == '6')
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (6).png"));
                    else
                        painter.drawPixmap(ty*w-w+w1, tx*h-h+h1, w, h, QPixmap(":/new/prefix1/block1 (7).png"));
            }
        }

    //绘制分数信息
    QFont font;            //设置字体
    font.setPointSize(10);  //字体大小为13
    painter.setFont(font);  //使用新建的字体
    painter.setPen(Qt::green); //字体颜色
    painter.setBrush(Qt::black);
    char s[10];
    char LEVEL[8][11]={"","困难","普通","","简单","","","手残"};
    sprintf(s, "%s\n", LEVEL[this->level]);
    painter.drawText(10*w+3*w1, 14*h+2*h1, "关卡难度");
    painter.drawText(12*w+4*w1, 14*h+2*h1, s);
    sprintf(s, "%3d",board->scoreRank[0]);
    painter.drawText(10*w+3*w1, 15*h+2*h1, "最高得分");
    painter.drawText(12*w+4*w1, 15*h+2*h1, s);
    sprintf(s, "%3d", board->score);
    painter.drawText(10*w+3*w1, 16*h+2*h1, "当前得分");
    painter.drawText(12*w+4*w1, 16*h+2*h1, s);

    if(stisexiting)//绘制道具
    {
        painter.drawPixmap(w1*2+11.5*w,6*h+0.5*h1, w*2, h*2,  QPixmap(":/new/prefix1/slowtoolt.jpg"));
    }
    else
    {
         painter.drawPixmap(w1*2+11.5*w,6*h+0.5*h1, w*2, h*2,  QPixmap(":/new/prefix1/slowtoolf.jpg"));
    }
    if(dtisexiting)
    {
        painter.drawPixmap(w1*2+11.5*w,8*h+1.5*h1, w*2, h*2,  QPixmap(":/new/prefix1/deltoolt.jpg"));
    }
    else
    {
        painter.drawPixmap(w1*2+11.5*w,8*h+1.5*h1, w*2, h*2,  QPixmap(":/new/prefix1/deltoolf.jpg"));
    }
    if(ctisexiting)
    {
        painter.drawPixmap(w1*2+11.5*w,10*h+2.5*h1, w*2, h*2,  QPixmap(":/new/prefix1/cleartoolt.jpg"));
    }
    else
    {
        painter.drawPixmap(w1*2+11.5*w,10*h+2.5*h1, w*2, h*2,  QPixmap(":/new/prefix1/cleartoolf.jpg"));
    }

    quitButton->setStyleSheet("border-image: url(:/new/prefix1/back3.png)");
    quitButton->setGeometry(10*w+3*w1,18*h+h1, w*2, h*2);
    quitButton->show();
    stopButton->setStyleSheet(tr("border-image: url(:/new/prefix1/pause3.png);"));
    stopButton->setGeometry(13*w+1*w1,18*h+h1, w*2, h*2);
    stopButton->show();

}

void MainWindow::timerEvent()
{

    if(board->brick->judge(3)){
        board->brick->moveDown();
    }
    else
    {

        timer->stop();
        board->add();
        if(board->isend())//游戏结束时并弹窗提示
        {
            slowtool=0,deltool=0,cleartool=0;
            stisexiting=false,dtisexiting=false,ctisexiting=false;
            timer->stop();
            //重玩
            if (QMessageBox::Yes ==
                    QMessageBox::question(this, tr("提醒"), tr("游戏结束,重新开始?"),
                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
            {
                QMessageBox::information(this, tr("提醒"), tr("准备开始！！"));

                board->brick->toNext();
                board->score = 0;

                //初始化地图
                for(int i=0; i<=21; i++)
                    for(int j=0; j<=11; j++)
                        board->map[i][j] = '#';
                for(int i=0; i<=21; i++)
                        board->map[i][0] = board->map[i][11] = '*';
                    for(int i=1; i<=10; i++)
                        board->map[21][i] = '*';
            }
            //退出
            else
            {
                QMessageBox::information(this, tr("游戏结束"), tr("游戏结束"));
                exit(1);
            }
        }
        timer->start();
    }
    //更新游戏界面（paintEvent（Event* ））
    this->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //回车键暂停游戏
    if(event->key() == Qt::Key_Return)
    {
        timer->stop();
        ispause = 1;
        QMessageBox::information(this, tr("提醒"), tr("回到游戏"));
        ispause = 0;
        timer->start();
    }

    //若处在暂停状态则忽略其他的按键
    if(ispause)
        return;
    if(event->key() == Qt::Key_Up)
    {
        if(board->brick->judge(0))
            board->brick->transform();
    }
    else if(event->key() == Qt::Key_Down)
    {
        if(board->brick->judge(3))
            board->brick->moveDown();
    }
    else if(event->key() == Qt::Key_Space)
    {
        if(board->brick->judge(3))
            board->brick->moveFinal();
    }
    else if(event->key() == Qt::Key_Left)
    {
        if(board->brick->judge(1))
            board->brick->moveLeft();
    }
    else if(event->key() == Qt::Key_Right)
    {
        if(board->brick->judge(2))
            board->brick->moveRight();
    }
    else if(event->key() == Qt::Key_1)
    {
        if(slowtool>0)
        {
            slowdown();
            slowtool--;
            if(slowtool==0)
            {
                stisexiting=false;
            }
        }
        else
        {
            return;
        }
    }
    else if(event->key() == Qt::Key_2)
    {
        if(deltool>0)
        {
            del();
            deltool--;
            board->score += 2*SCORE ;
            if(deltool==0)
            {
                dtisexiting=false;
            }
        }
        else
        {
            return;
        }
    }
    else if(event->key() == Qt::Key_3)
    {
        if(cleartool>0)
        {
            clearall();
            board->score += 5*SCORE ;
            cleartool--;
            if(cleartool==0)
            {
                ctisexiting=false;
            }
        }
        else
        {
            return;
        }
    }
    //更新界面
    this->update();
}
