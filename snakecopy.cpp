#include "snakecopy.h"

partpos::partpos(int col, int row)
{
    x=col;
    y=row;
}

partpos::partpos()
{
    x=y=0;
}
snakegame::snakegame()
{
    initscr();
    nodelay(stdscr,true); //뭐 누를때까지 getch 안기달림
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, maxheight, maxwidth);
    maxwidth -= 20;
    //초기화
    partchar='x';
    oldalchar=(char)219;
    foo='O';
    poison='@';
    rItem = 1;
    itemCnt = 0;
    growthItem.x=0;
    growthItem.y=0;
    poisonItem.x=0;
    poisonItem.y=0;
    snakeLength = 5;
    usingGate = 0;
    eatFood = 0;
    eatPoison = 0;

    for(int i =0;i<5;i++)
        snake.push_back(partpos(40+i,10));
    points=0;
    del=110000;
    get=false;
    checked = 0;
    direction='l';
    srand(time(0));
    putfood();
    for(int i=0;i<maxwidth-1;i++)
    {
        move(0,i);
        addch(oldalchar);
    }
    for(int i=0;i<maxwidth-1;i++)
    {
        move(maxheight-2,i);
        addch(oldalchar);
    }
    for(int i=0;i<maxheight-1;i++)
    {
        move(i,0);
        addch(oldalchar);
    }
    for(int i=0;i<maxheight-1;i++)
    {
        move(i,maxwidth-2);
        addch(oldalchar);
    }
    for(int i=0;i<snake.size();i++){
        move(snake[i].y,snake[i].x);
        addch(partchar);
    }
    move(maxheight-1,0);
    showpoint();
    move(growthItem.y,growthItem.x);
    addch(foo);
    refresh();
}
snakegame::~snakegame()
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snakegame::putfood()
{
    bool isoverlap;
    while(true)
    {
        isoverlap = false;
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++){
            if(snake[i].x==tmpx && snake[i].y==tmpy)
            {
                isoverlap=true;
                break;
            }
        }
        if(isoverlap)
            continue;
        if(tmpx>maxwidth-3 ||tmpy>maxheight-4){
            continue;
        }
        growthItem.x=tmpx;
        growthItem.y=tmpy;
        moveItem.x=tmpx;
        moveItem.y=tmpy;
        break;
    }
    move(growthItem.y,growthItem.x);
    addch(foo);
    refresh();
}

void snakegame::putpoison()
{
    bool isoverlap;
    while(true)
    {
        isoverlap = false;
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++){
            if(snake[i].x==tmpx && snake[i].y==tmpy)
            {
                isoverlap=true;
                break;
            }
        }
        if(isoverlap)
            continue;
        if(tmpx>maxwidth-3 ||tmpy>maxheight-4){
            continue;
        }
        poisonItem.x=tmpx;
        poisonItem.y=tmpy;
        moveItem.x=tmpx;
        moveItem.y=tmpy;
        break;
    }
    move(poisonItem.y,poisonItem.x);
    addch(poison);
    refresh();
}

void snakegame::putItem()
{
    itemCnt = 0;
    rItem = rand()%2;
    if(rItem == 0){
        putfood();
    }
    else{
        putpoison();
    }
}

void snakegame::showpoint()
{
    move(2,maxwidth-1);
    printw("   YOUR SCORE");
    move(3,maxwidth-1);
    printw("   -----------");
    move(4,maxwidth-1);
    printw("   Point: \t %d",points);
    move(5,maxwidth-1);
    printw("   Size: \t %d",snakeLength);
    move(6,maxwidth-1);
    printw("   O: \t %d",eatFood);
    move(7,maxwidth-1);
    printw("   @: \t %d",eatPoison);
    move(8,maxwidth-1);
    printw("   Gate: \t %d",usingGate);

}

bool snakegame::collision()
{
    if(snake[0].x==0 || snake[0].x==maxwidth-1||snake[0].y==0||snake[0].y==maxheight-2)
        return true;
    
    for(int i=2;i<snake.size();i++){
        if(snake[0].x==snake[i].x &&snake[0].y==snake[i].y)
            return true;
    }
    if(snake[0].x==growthItem.x&&snake[0].y==growthItem.y){
        checked=1;
        putItem();
        points+=15;
        snakeLength++;
        eatFood++;
        move(maxheight-1,0);
        showpoint();
        if((points%100)==0)
            del-=10000;
    }
    else if(snake[0].x==poisonItem.x&&snake[0].y==poisonItem.y){
        checked=2;
        putItem();
        points+=10;
        snakeLength--;
        eatPoison++;
        move(maxheight-1,0);
        showpoint();
        if((points%100)==0)
            del-=10000;
        if(snake.size() <= 3){
            move(snake[snake.size()-1].y,snake[snake.size()-1].x);
            addch(' ');
            refresh();
            snake.pop_back();
            return true;
        }
    }
    else
    {
        checked=0;
    }
    return false;
}
void snakegame::movesnake()
{
    int tmp=getch();
    itemCnt += 1;
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
    if(checked == 0)
    {
        move(snake[snake.size()-1].y,snake[snake.size()-1].x);
        addch(' ');
        refresh();
        snake.pop_back();
    }
    if(checked == 2){
        move(snake[snake.size()-1].y,snake[snake.size()-1].x);
        addch(' ');
        refresh();
        snake.pop_back();
        move(snake[snake.size()-1].y,snake[snake.size()-1].x);
        addch(' ');
        refresh();
        snake.pop_back();
    }
    if(itemCnt >= 120){
        move(moveItem.y, moveItem.x);
        addch(' ');
        growthItem.x = 0;
        growthItem.y = 0;
        poisonItem.x = 0;
        poisonItem.y = 0;
        putItem();
    }
    if(direction=='l'){
        snake.insert(snake.begin(),partpos(snake[0].x-1,snake[0].y));
    }
    else if (direction=='r'){
        snake.insert(snake.begin(),partpos(snake[0].x+1,snake[0].y));
    }
    else if (direction=='u'){
        snake.insert(snake.begin(),partpos(snake[0].x,snake[0].y-1));
    }
    else if (direction=='d'){
        snake.insert(snake.begin(),partpos(snake[0].x,snake[0].y+1));
    }
    move(snake[0].y,snake[0].x);
    addch(partchar);
    refresh();
}

void snakegame::start()
{
    direction='u';
    while(1)
    {
        if(collision())
        {
            move(maxheight/2,maxwidth/2);
            printw("game over");
            break;
        }
    movesnake();
    if(direction=='q')
        break;
    usleep(del);
    }
}
