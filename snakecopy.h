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
    int points, del, maxwidth, maxheight;
    char direction, partchar, oldalchar, foo;
    bool get;
    partpos growthItem;
    std::vector<partpos> snake;

    void putfood();
    bool collision();
    void movesnake();
public:
    snakegame();
    ~snakegame();
    void start();
};
#endif