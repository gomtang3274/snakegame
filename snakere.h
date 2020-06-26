#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#ifndef SNAKE_H
#define SNAKE_H

struct partpos{
    int x,y;
    partpos(int col, int row);
    partpos();
};

class snakegame{
    int points, del, maxwidth, maxheight, itemWhat, itemRandom, itemCnt, snakeLength, eatFood, eatPoison, phase, scorephase;
    int requiredFood, requiredPoison, requiredSize;
    char direction;
    bool show;
    bool mission1, mission2, missionF, missionP, missionS;
    partpos itemFood, itemPoison, itemMove;
    std::vector<partpos> snake;
    std::vector<partpos> wall;

    void putFood();
    void putPoison();
    void chooseItem();
    bool collision();
    void movesnake();
    void showpoint();
    void map1(int y, int x);
    void map2(int y, int x);
    void mapDrawing();
    void gameover();
    void missionCheck();
public:
    snakegame();
    ~snakegame();
    void start();
};
#endif