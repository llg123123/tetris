#include "brick.h"
#include "board.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <QPainter>



using namespace std;



Brick::Brick(Board *board)

{

    this->board = board;

    x = -3;

    y = 4;

    //随机数确定第一个块的类型

    type = random();
    nexttype = random();

    //读入方块类型
        char b[19][5][5]=
                {
            {
                                "1###",
                                "11##",
                                "#1##",
                                "####"
                                },
                                {
                                "#11#",
                                "11##",
                                "####",
                                "####"
                                },
                                {
                                "#2##",
                                "22##",
                                "2###",
                                "####"
                                },
                                {
                                "22##",
                                "#22#",
                                "####",
                                "####"
                                },
                                {
                                "#3##",
                                "#3##",
                                "#33#",
                                "####"
                                },
                                {
                                "####",
                                "333#",
                                "3###",
                                "####"
                                },
                                {
                                "33##",
                                "#3##",
                                "#3##",
                                "####"
                                },
                                {
                                "##3#",
                                "333#",
                                "####",
                                "####"
                                },
                                {
                                "#4##",
                                "#4##",
                                "44##",
                                "####"
                                },
                                {
                                "4###",
                                "444#",
                                "####",
                                "####"
                                },
                                {
                                "#44#",
                                "#4##",
                                "#4##",
                                "####"
                                },
                                {
                                "####",
                                "444#",
                                "##4#",
                                "####"
                                },
                                {
                                "#5##",
                                "555#",
                                "####",
                                "####"
                                },
                                {
                                "#5##",
                                "#55#",
                                "#5##",
                                "####"
                                },
                                {
                                "####",
                                "555#",
                                "#5##",
                                "####"
                                },
                                {
                                "#5##",
                                "55##",
                                "#5##",
                                "####"
                                },
                                {
                                "#6##",
                                "#6##",
                                "#6##",
                                "#6##"
                                },
                                {
                                "####",
                                "6666",
                                "####",
                                "####"
                                },
                                {
                                "77##",
                                "77##",
                                "####",
                                "####"
                                }
        };

    for(int i=0;i<19;i++)
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
            block[i][j][k]=b[i][j][k];

    //next数组模拟指向，用于方块旋转功能
    int tempNext[19]={1,0,3,2,5,6,7,4,9,10,11,8,13,14,15,12,17,16,18};
    for(int i=0; i<19; i++)
        next[i]=tempNext[i];

}
//改变块为下一个块，并随机更新下一个块类型

void Brick::toNext()
{
    x = -3;
    y = 4;
    type = nexttype;
    nexttype = random();

}


//旋转
void Brick::transform()
{
    type = next[type];
}


//加速向下
void Brick::moveDown()
{
    x++;
}

void Brick::moveFinal()
{
    while(judge(3))
    {
        x++ ;
    }
}

//左移
void Brick::moveLeft()

{
    y--;
}

//右移
void Brick::moveRight()

{
    y++;
}


//碰撞检测
bool Brick::judge(int flag)

{
    int nextX, nextY, nextType;
    switch(flag)
    {
        case 0: nextX = x; nextY = y; nextType = next[type]; break;
        case 3: nextX = x+1; nextY = y; nextType = type; break;
        case 1: nextX = x; nextY = y-1; nextType = type; break;
        case 2: nextX = x; nextY = y+1; nextType = type; break;
    }
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int tx = nextX+i;
            int ty = nextY+j;
            if(tx < 0 || tx > 21 || ty < 0 || ty > 11)
                continue;
            if(block[nextType][i][j] != '#'&& (ty == 0 || ty == 11))
                return false;
            if(block[nextType][i][j] != '#' && board->map[tx][ty] != '#' )
                return false;
        }

    return true;

}

int Brick :: random()
{
    int icount[7]={2,2,4,4,4,2,1};
    srand(time(NULL));
    int Type = rand() % 7 , sum =0;
    for (int i = 0; i < Type; i++)
        sum += icount[i];
    return sum + rand() % icount[Type];
}
