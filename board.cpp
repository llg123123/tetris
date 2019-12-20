#include "board.h"

#include "brick.h"

#include <fstream>

#include <iostream>
#include<QTime>
#include <QtGlobal>

using namespace std;
extern int slowtool,deltool,cleartool;
extern bool stisexiting,dtisexiting,ctisexiting;
int p=0;

Board::Board()
{

    //初始化块，时间间隔，分数

    brick = new Brick(this);
    score = 0 ;

    //从文件读入最高分

    FILE *fd =fopen("D:\\record.txt","r+");
    for(int i=0;i<10;i++)
        fscanf(fd, "%d", scoreRank+i);

    //初始化地图

    for(int i=0; i<=21; i++)

        for(int j=0; j<=11; j++)

            map[i][j] = '#';
    for(int i=0; i<=21; i++)
            map[i][0] = map[i][11] = '*';
        for(int i=1; i<=10; i++)
            map[21][i] = '*';

}

void Board::add()

{
    //将块更新到map
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            int tx = brick->x + i;
            int ty = brick->y + j;
            if(tx<1 || tx > 20 || ty < 1 || ty > 10)
                continue;
            if(brick->block[brick->type][i][j] != '#')
                map[tx][ty] = brick->block[brick->type][i][j];
        }

    //消去完整的行并计算行个数
    int cnt = 0;
    for(int i=20; i>=1; i--)
    {
        bool flag = false;
        for(int j=1; j<=10; j++)
            if(map[i][j] == '#')
            {
                flag = true;
                break;
            }
        if(flag)
            continue;
        cnt++;
        for(int j=i; j>=1; j--)
            for(int k=1; k<=10; k++)
                map[j][k] = map[j-1][k];
        i++;
    }

    if(cnt)
        score += SCORE*cnt;

    if(score%30==0&&score!=30*p&&cnt>0)//只有未用道具消去的行数才会获得道具
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int t=qrand()%3;
        if(t==0)
        {
            slowtool++;
            stisexiting=true;
        }
        else if(t==1)
        {
            deltool++;
            dtisexiting=true;
        }
        else if(t==2)
        {
            cleartool++;
            ctisexiting=true;
        }
        p++;
    }
    brick->toNext();
}

bool Board::isend()

{
    for(int i=1; i<=10; i++)
        if(map[1][i] != '#')
        {
            //如果游戏结束，计入排行榜
            for(int i=0;i<10;i++)
                   {
                       if(score > scoreRank[i])
                       {
                           for(int j= 9 ; j > i ; j --)
                               scoreRank[j]=scoreRank[j-1];
                           scoreRank[i]= score;
                           break;
                       }
            }
            FILE *fd =fopen("D:\\record.txt","w+");
            for(int i=0;i<10;i++)
                fprintf(fd, "%d\n", scoreRank[i]);
            fclose(fd);
            return true;
        }
    return false;

}
