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
    int points, del, maxwidth, maxheight, checked, rItem, itemCnt;
    char direction, partchar, oldalchar, foo, poison;
    bool get;
    partpos growthItem, poisonItem, moveItem;
    std::vector<partpos> snake;

    void putfood();
    void putpoison();
    void putItem();
    bool collision();
    void movesnake();
public:
    snakegame();
    ~snakegame();
    void start();
};
#endif