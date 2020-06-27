#include <iostream>
#include <deque>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#ifndef SNAKE_H
#define SNAKE_H

struct partpos{
    int x,y;
    partpos(int row, int col);
    partpos();
};
/*
wall의 open이
'a'이면 다뚫, (나올때 방향 그대로)
'n'이면 수평+위쪽, (d로 들어오면 l로 방향전환, 나머지는 그대로)
'e'이면 수직+오른쪽, (l로 들어오면 u로 방향전환, 나머지는 그대로)
's'이면 수평+아래쪽, (u로 들어오면 r로 방향전환, 나머지는 그대로)
'w'이면 수직+왼쪽, (r로 들어오면 d로 방향전환, 나머지는 그대로)
'h'이면 수평, (r로 들어오면 d로, l로 들어오면 u로 방향전환, 나머지는 그대로)
'v'이면 수직, (d로 들어오면 l로, u로 들어오면 r로 방향전환, 나머지는 그대로)
'1'이면 위+오른쪽, (d로 들어오면 r로, l로 들어오면 u로 방향전환, 나머지는 그대로)
'2'이면 위+왼쪽, (d로 들어오면 l로, r로 들어오면 u로 방향전환, 나머지는 그대로)
'3'이면 아래+왼쪽, (u로 들어오면 l로, r로 들어오면 d로 방향전환, 나머지는 그대로)
'4'이면 아래+오른쪽, (u로 들어오면 r로, l로 들어오면 d로 방향전환, 나머지는 그대로)
'r'이면 오른쪽, (방향 r로)
'l'이면 왼쪽, (방향 l로)
'u'이면 위쪽, (방향 u로)
'd'이면 아래쪽으로 뚫림. (방향 d로)
*/
struct wall{
    int y,x;
    char open;
    wall(int row, int col, char dir);
    wall();
};

class snakegame{
    const int maxwidth = 30;
    const int maxheight = 30;
    const int del = 30;

    //itemWhat=0일때 아무것도 안먹,1일때 성장, 2일때 독약, 3일때 2관문으로감, 4일때 1관문으로 감.
    int points, itemWhat, itemRandom, itemCnt, snakeLength, eatFood, eatPoison, phase, scorephase;
    int requiredFood, requiredPoison, requiredSize, requiredGate, gatePoint, ingateTime;
    char direction;
    bool show;
    bool gExist, inGate;
    bool mission1, mission2, mission3, mission4, missionF, missionP, missionS, missionG,gameSuccess;
    int errorchk;
    
    partpos itemFood, itemPoison, itemMove;
    wall gate1, gate2;
    std::deque<partpos> snake;
    std::vector<wall> walls;
    std::string gameMap[30];//벽='w', 모서리='W', 빈공간='b', 성장='f', 독='p', 관문1='g', 관문2='G', 뱀머리='S', 뱀몸='s'

    void putFood();
    void putPoison();
    void putGate();
    void chooseItem();
    bool collision();
    void movesnake();
    void showpoint();
    //void map1(int y, int x);
    //void map2(int y, int x);
    //void mapDrawing();
    void makeMap(int stage);
    void gameover();
    void missionCheck();
public:
    snakegame();
    ~snakegame();
    void start();
};
#endif