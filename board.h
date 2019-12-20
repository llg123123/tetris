#ifndef BOARD_H

#define BOARD_H
#define SCORE 30
#include "brick.h"

class Brick;

class Board

{

public:

    int score;//当前分数

    int scoreRank[10];

    Brick *brick;//下落的方块

    char map[100][100];//保存地图信息

    Board();

    void add();//将下落到底的块更新到map

    bool isend();//判断是否游戏结束

};



#endif // BOARD_H
