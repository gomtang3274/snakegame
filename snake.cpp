#include "snake.h"


partpos::partpos(int col, int row)
{
    x=col;
    y=row;
}

partpos::partpos()
{
    x=y=0;
}
wall::wall(int col, int row, char dir){
    x = col;
    y = row;
    open = dir;
}
wall::wall(){
    x = y =0;
    open = 'a';
}
snakegame::snakegame()
{
    initscr();
    start_color();
    nodelay(stdscr,true); //뭐 누를때까지 getch 안기달림
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    //초기화
    ////지형지물 색깔입히기
        //빈공간색
    init_pair(1,0,255); 
        //뱀머리색
    init_pair(2,0,220);
        //뱀몸통색
    init_pair(3,0,228);
        //벽색
    init_pair(4,0,243);
        //모서리벽색
    init_pair(5,0,232);
        //성장색
    init_pair(6,0,154);
        //독색
    init_pair(7,0,196);
        //관문색
    init_pair(8,0,129);
    
    attron(growthColor);
    
    /* 맵 만드는 과정
    partchar='x';
    oldalchar=(char)219;
    foo='*';
    growthItem.x=0;
    growthItem.y=0;
    for(int i =0;i<5;i++)
        snakeBody.push_back(partpos(13+i,15));
    growthPoints=0;
    gotGrowth=false;
    direction='l';
    srand(time(0));
    putGrowth();
    //wall
    for(int i=0;i<gameWidth-1;i++)
    {
        move(0,i);
        addch(oldalchar);
    }
    for(int i=0;i<gameWidth-1;i++)
    {
        move(gameHeight-2,i);
        addch(oldalchar);
    }
    for(int i=0;i<gameHeight-1;i++)
    {
        move(i,0);
        addch(oldalchar);
    }
    for(int i=0;i<gameHeight-1;i++)
    {
        move(i,gameWidth-2);
        addch(oldalchar);
    }
    for(int i=0;i<snakeBody.size();i++){
        move(snakeBody[i].y,snakeBody[i].x);
        addch(partchar);
    }
    move(gameHeight-1,0);
    printw("%d",growthPoints);
    move(growthItem.y,growthItem.x);
    addch(foo);
    refresh();
    */
}
snakegame::~snakegame()
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snakegame::putGrowth()
{
    srand(time(0));
    int tmpx=rand()%(gameWidth-1)+1;
    int tmpy=rand()%(gameHeight-1)+1;
    while (gameMap[tmpy][tmpx]!='b')
    {
        srand(time(0));
        tmpx=rand()%(gameWidth-1)+1;
        tmpy=rand()%(gameHeight-1)+1;
    }
    growthItem.x=tmpx;
    growthItem.y=tmpy;
    move(growthItem.y,growthItem.x);
    addch(foo);
    refresh();
}

bool snakegame::collision()
{   
    for(int i=2;i<snakeBody.size();i++){
        if(snakeBody[0].x==snakeBody[i].x &&snakeBody[0].y==snakeBody[i].y)
            return true;
    }
    return false;
}
void snakegame::movesnake()
{
    int tmp=getch();
    switch (tmp)
    {
    case KEY_LEFT:
        if(direction!='r')
            direction='l';
        break;
    case KEY_UP:
        if(direction='d')
            direction='u';
        break;
    case KEY_DOWN:
        if(direction!='u')
            direction='d';
        break;
    case KEY_RIGHT:
        if(direction!='l')
            direction='r';
        break;
    case KEY_BACKSPACE:
        direction='q';
        break;
    }
    if(!gotGrowth)
    {
        move(snakeBody[snakeBody.size()-1].y,snakeBody[snakeBody.size()-1].x);
        addch(' ');
        refresh();
        snakeBody.pop_back();
    }
    if(direction=='l'){
        if(snakeBody[0].x-1==0)
            snakeBody.push_front(partpos(gameWidth-3,snakeBody[0].y));
        else
            snakeBody.push_front(partpos(snakeBody[0].x-1,snakeBody[0].y));
    }
    else if (direction=='r'){
        if(snakeBody[0].x+1==gameWidth-2)
            snakeBody.push_front(partpos(1,snakeBody[0].y));
        else
            snakeBody.push_front(partpos(snakeBody[0].x+1,snakeBody[0].y));
    }
    else if (direction=='u'){
        if(snakeBody[0].y-1==0)
            snakeBody.push_front(partpos(snakeBody[0].x,gameHeight-3));
        else
            snakeBody.push_front(partpos(snakeBody[0].x,snakeBody[0].y-1));
    }
    else if (direction=='d'){
        if(snakeBody[0].y+1==gameHeight-2)
            snakeBody.push_front(partpos(snakeBody[0].x,1));
        else
            snakeBody.push_front(partpos(snakeBody[0].x,snakeBody[0].y+1));
    }
    move(snakeBody[0].y,snakeBody[0].x);
    addch(partchar);
    refresh();
    flushinp();
}

void snakegame::start()
{
    while(gameOn){
        switch (phase)
        {
        case Menu:
            /* 미구현 */
            break;
        
        case inGame:
            direction='u';
            while(1)
            {
            movesnake();
                if(collision())
                {
                    move(12,36);
                    printw("game over");
                    break;
                }
            if(direction=='q')
                break;
            usleep(timeDelay);
            }
            break;
        }
    }
    
}

void snakegame::startgame(int stage)
{
    makemap(stage);
}

void snakegame::makemap(int stage)
{
    std::string mapName = "map/map*.txt";
    std::string wallposName = "map/wallpos*.txt";
    std::ifstream maptext;
    int i,row,column,dir,txtcount, wallcount = 112;

    maptext.open(mapName.replace(7,1,std::to_string(stage)));
    maptext>>goalLength>>goalGrowth>>goalPoison>>goalGate;
    maptext>>txtcount>>direction;
    for(i =0;i<txtcount;i++){
        maptext>>row>>column;
        snakeBody.push_back(partpos(row,column));
    }
    if(gameMap.size()){
        for(i =0;i<30;i++){
            std::getline(maptext,gameMap[i]);
        }
    }
    else{
        gameMap.resize(30);
        for(i =0;i<30;i++){
            std::getline(maptext,gameMap[i]);
        }
    }
    maptext.close();
    maptext.open(wallposName.replace(11,1,std::to_string(stage)));
    walls.clear();
    maptext>>txtcount;
    wallcount+=txtcount;
    walls.reserve(wallcount);
    for(column=1;column<29;column++){
        walls.push_back(wall());
    }
    maptext.close();
    //벽='w', 모서리='W', 빈공간='b', 성장='g', 독='p', 관문1='q', 관문2='Q', 뱀머리='S', 뱀몸='s'
}