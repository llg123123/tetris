#include "menu.h"
#include "ui_menu.h"
 #include <QPixmap>
#include <QPalette>
#include <QBitmap>
#include<help.h>
menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    //音乐播放
       effect = new QSoundEffect (this);
       effect->setLoopCount(QSoundEffect::Infinite);
       effect->setSource(QUrl::fromLocalFile("D:/music/music1.wav"));
       effect->setVolume(0.1);

    ui->setupUi(this);
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->radioButton_3->hide();
    ui->radioButton_4->hide();
    ui->radioButton_5->hide();
    ui->radioButton_6->hide();
    ui->radioButton_7->hide();
    ui->radioButton_8->hide();
    ui->radioButton_9->hide();

    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();

    ui->pushButton_4->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();

    ui->horizontalSlider->hide();

    level = 4;//默认为简单
    backpictureID = 1;  //默认第一张背景图片
    ui->buttonGroup->setId(ui->radioButton,7);//关卡难度的编号
    ui->buttonGroup->setId(ui->radioButton_2,4);
    ui->buttonGroup->setId(ui->radioButton_3,2);
    ui->buttonGroup->setId(ui->radioButton_4,1);

    ui->buttonGroup_2->setId(ui->radioButton_5,1);   //背景图片的编号
    ui->buttonGroup_2->setId(ui->radioButton_6,2);
    ui->buttonGroup_2->setId(ui->radioButton_7,3);
    ui->buttonGroup_2->setId(ui->radioButton_8,4);
    ui->buttonGroup_2->setId(ui->radioButton_9,5);


    QPixmap bgImages(":/new/prefix1/menu.jpg");   //开始界面
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());// set background mask attribute same as background's image


}

menu::~menu()
{
    delete ui;
    delete w;
}

void menu::on_pushButton_clicked()    //进入游戏按键
{
    Board *board = new Board();

    w = new MainWindow(board,level,backpictureID);

    this->hide(); //实现先隐藏再进入游戏

    w->show();
}

void menu::on_pushButton_2_clicked()   //选项界面
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_5->hide();
    ui->pushButton_9->hide();


    QPixmap bgImages(":/new/prefix1/menu2.JPG");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());

    ui->pushButton_4->show();
    ui->radioButton->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();

    ui->horizontalSlider->show();
    ui->radioButton_2->show();
    ui->radioButton_3->show();
    ui->radioButton_4->show();
    ui->radioButton_5->show();
    ui->radioButton_6->show();
    ui->radioButton_7->show();
    ui->radioButton_8->show();
    ui->radioButton_9->show();

    ui->label->show();
    ui->label_2->show();


     QPixmap pixmap(":/new/prefix1/background1.jpg");
     pixmap.scaled(ui->label_3->size(), Qt::KeepAspectRatio);
     ui->label_3->setScaledContents(true);
     ui->label_3->setPixmap(pixmap);
}


void menu::on_pushButton_3_clicked() //退出
{
    this -> close();
}


void menu::on_pushButton_4_clicked()
{
    level = ui->buttonGroup->checkedId();
    backpictureID = ui->buttonGroup_2->checkedId();

    if (level == -1) level = 2;
    if (backpictureID == -1) backpictureID = 1;


    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->radioButton_3->hide();
    ui->radioButton_4->hide();
    ui->radioButton_5->hide();
    ui->radioButton_6->hide();
    ui->radioButton_7->hide();
    ui->radioButton_8->hide();
    ui->radioButton_9->hide();

    ui->label->hide();
    ui->label_2->hide();

    ui->pushButton_4->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->horizontalSlider->hide();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_5->show();
    ui->pushButton_9->show();
    QPixmap bgImages(":/new/prefix1/menu.jpg");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());

    ui->label_3->hide();

}



//游戏背景图片设置
void menu::on_radioButton_5_clicked()
{

    QPixmap pixmap(":/new/prefix1/background1.jpg");
    ui->label_3->setPixmap(pixmap);
    ui->label_3->show();
}

void menu::on_radioButton_6_clicked()
{
    QPixmap pixmap(":/new/prefix1/background2.jpg");
    ui->label_3->setPixmap(pixmap);
    ui->label_3->show();
}

void menu::on_radioButton_7_clicked()
{
    QPixmap pixmap(":/new/prefix1/background3.jpg");
    ui->label_3->setPixmap(pixmap);
    ui->label_3->show();
}

void menu::on_radioButton_8_clicked()
{
    QPixmap pixmap(":/new/prefix1/background4.jpg");
    ui->label_3->setPixmap(pixmap);
    ui->label_3->show();
}

void menu::on_radioButton_9_clicked()
{
    QPixmap pixmap(":/new/prefix1/background5.jpg");
    ui->label_3->setPixmap(pixmap);
    ui->label_3->show();
}

void menu::on_pushButton_5_clicked()  //排行榜按键
{
    QPixmap bgImages(":/new/prefix1/menu2.JPG");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_5->hide();
    ui->pushButton_9->hide();
    int scoreRank[10];
    FILE *fd =fopen("D:\\record.txt","r+");
    for(int i=0;i<10;i++)
        fscanf(fd, "%d", scoreRank+i);

    QFont font ("Microsoft YaHei", 13, 75);
    ui->label_4->setFont(font);
    ui->label_4->setStyleSheet("color:white;");
    ui->label_4->setText(
               "第一名：\t\t"+QString::number(scoreRank[0])
            +"\n第二名:\t\t"+QString::number(scoreRank[1])
            +"\n第三名:\t\t"+QString::number(scoreRank[2])
            +"\n第四名:\t\t"+QString::number(scoreRank[3])
            +"\n第五名:\t\t"+QString::number(scoreRank[4])
            +"\n第六名:\t\t"+QString::number(scoreRank[5])
            +"\n第七名:\t\t"+QString::number(scoreRank[6])
            +"\n第八名:\t\t"+QString::number(scoreRank[7])
            +"\n第九名:\t\t"+QString::number(scoreRank[8])
            +"\n第十名:\t\t"+QString::number(scoreRank[9])
            );
    ui->label_4->show();
    ui->pushButton_6->show();
}

void menu::on_pushButton_6_clicked()
{

    QPixmap bgImages(":/new/prefix1/menu.jpg");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());
    ui->label_4->hide();
    ui->pushButton_6->hide();
    ui->pushButton->show();
    ui->pushButton_2->show();
    ui->pushButton_3->show();
    ui->pushButton_5->show();
    ui->pushButton_9->show();
}

void menu::on_horizontalSlider_sliderMoved(int position)
{
    double d_position=position*1.0/100.0;
    effect->setVolume(d_position);
}

void menu::on_pushButton_8_clicked()
{
    if(flag%2==0)
       {
           effect->play();
           ui->pushButton_8->setStyleSheet(tr("border-image: url(:/new/prefix1/musicStop.png);"));
           flag++;
       }
       else
       {
           effect->stop();
           ui->pushButton_8->setStyleSheet(tr("border-image: url(:/new/prefix1/musicStart.png);"));
           flag++;
       }
}

void menu::on_pushButton_7_clicked()  //背景音乐
{
        flag2++;
        switch(flag2%7)
        {
        case 1:
            effect->setSource(QUrl::fromLocalFile("D:music/music1.wav"));
            break;
        case 2:
            effect->setSource(QUrl::fromLocalFile("D:music/music2.wav"));
            break;
        case 3:
            effect->setSource(QUrl::fromLocalFile("D:music/music3.wav"));
            break;
        case 4:
            effect->setSource(QUrl::fromLocalFile("D:music/music8.wav"));
            break;
        case 5:
            effect->setSource(QUrl::fromLocalFile("D:music/music5.wav"));
            break;
        case 6:
            effect->setSource(QUrl::fromLocalFile("D:music/music6.wav"));
            break;
        case 7:
            effect->setSource(QUrl::fromLocalFile("D:music/music7.wav"));
            break;
        }
        if(flag%2==1)
        {
            effect->play();
        }
}


void menu::on_pushButton_9_clicked()
{
    this->close();
    help *m=new help();
    m->show();
}
