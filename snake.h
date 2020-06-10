#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#ifndef SNAKE_H
#define SNAKE_H


//요소들의 좌표값
struct partpos{
    int x,y;
    partpos(int col, int row);
    partpos();
};
/*
wall의 open이
'a'이면 다뚫,
'n'이면 수평+위쪽,
'e'이면 수직+오른쪽,
's'이면 수평+아래쪽,
'w'이면 수직+왼쪽,
'h'이면 수평,
'v'이면 수직,
'1'이면 위+오른쪽,
'2'이면 위+왼쪽,
'3'이면 아래+왼쪽,
'4'이면 아래+오른쪽,
'r'이면 오른쪽,
'l'이면 왼쪽,
'u'이면 위쪽,
'd'이면 아래쪽으로 뚫림.
*/
struct wall{
    int x,y;
    char open;
    wall(int col, int row, char dir);
    wall();
};

class snakegame{
    const int gameWidth = 30;
    const int gameHeight = 30;
    const int timeDelay = 110000;
    const chtype blankColor = COLOR_PAIR(1);
    const chtype snakeHColor = COLOR_PAIR(2);
    const chtype snakeBColor = COLOR_PAIR(3);
    const chtype wallColor = COLOR_PAIR(4);
    const chtype cornerColor = COLOR_PAIR(5);
    const chtype growthColor = COLOR_PAIR(6);
    const chtype poisonColor = COLOR_PAIR(7);
    const chtype gateColor = COLOR_PAIR(8);

    
    int snakeLength, growthPoints, poisonPoints, gatePoints;
    char direction, partchar, oldalchar, foo;
    bool gotGrowth, gotPoison;
    partpos growthItem, poisonItem;
    wall gate1, gate2;
    std::vector <std::string> gameMap;
    std::vector <wall> walls;
    std::deque<partpos> snakeBody;

    void putGrowth();
    void putPoison();
    bool collision();
    void startgame(int stage);
    void makemap(int stage);
    void movesnake();
public:
    snakegame();
    ~snakegame();
    void start();
};
#endif