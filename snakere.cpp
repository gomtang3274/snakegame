#include "snakere.h"

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
    //화면을 구성하는 색깔들
    start_color();
    init_pair(1,0,255);     //빈공간
    init_pair(2,0,243);     //벽
    init_pair(3,0,232);     //모서리벽
    init_pair(4,0,220);     //뱀머리
    init_pair(5,0,228);     //뱀몸통
    init_pair(6,0,154);     //음식
    init_pair(7,0,196);     //독
    init_pair(8,0,129);     //게이트
    init_pair(9,255,0);     //스코어창
    init_pair(10,1,255);    //게임오버
    init_pair(11,220,0);    //미션성공여부

    noecho();
    curs_set(0);
    show = false;
    phase = 1;      // 1단계
    points= 0;      //점수
    del=110000;
    srand(time(0)); // 변수고정
    getmaxyx(stdscr, maxheight, maxwidth); //화면의 가로 세로 길이를 받아 온다.


    //크기가 작은 화면에서는 오류 방지를 위해 스코어창을 표시하지 않는다.
    if(maxwidth>40){
        maxwidth -= 25;
        show = true;    //스코어창 표시
    }
    //초기화
    
}
snakegame::~snakegame()
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

//아이템 - 음식
void snakegame::putFood()
{
    bool replay;    //잘못된 위치 방지
    while(true)
    {
        replay = false;
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++){
            if(snake[i].x==tmpx && snake[i].y==tmpy)    //아이템 위치가 뱀과 겹쳤을 때
            {
                replay=true;
                break;
            }
        }
        for(int i=0;i<wall.size();i++){
            if(wall[i].x==tmpx && wall[i].y==tmpy)      //아이템 위치가 벽과 겹쳤을 때
            {
                replay=true;
                break;
            }
        }
        if(replay)
            continue;
        if(tmpx>maxwidth-2 ||tmpy>maxheight-3){         //아이템 위치가 게임 화면을 벗어날 때
            continue;
        }

        //아이템위치설정
        itemFood.x=tmpx;
        itemFood.y=tmpy;
        itemPoison.x=0;
        itemPoison.y=0;
        itemMove.x=tmpx;
        itemMove.y=tmpy;
        break;
    }
    move(itemFood.y,itemFood.x);
    attron(COLOR_PAIR(6));
    addch(' ');
    refresh();
}

void snakegame::putPoison()
{
    bool replay;
    while(true)
    {
        replay = false;
        int tmpx=rand()%maxwidth+1;
        int tmpy=rand()%maxheight+1;
        for(int i=0;i<snake.size();i++){
            if(snake[i].x==tmpx && snake[i].y==tmpy)
            {
                replay=true;
                break;
            }
        }
        for(int i=0;i<wall.size();i++){
            if(wall[i].x==tmpx && wall[i].y==tmpy)
            {
                replay=true;
                break;
            }
        }
        if(replay)
            continue;
        if(tmpx>maxwidth-2 ||tmpy>maxheight-3){
            continue;
        }
        itemFood.x = 0;
        itemFood.y = 0;
        itemPoison.x=tmpx;
        itemPoison.y=tmpy;
        itemMove.x=tmpx;
        itemMove.y=tmpy;
        break;
    }
    move(itemPoison.y,itemPoison.x);
    attron(COLOR_PAIR(7)); //독
    addch(' ');
    refresh();
}

void snakegame::chooseItem()
{
    itemCnt = 0;
    itemRandom = rand()%4;
    if(itemRandom != 0){
        putFood();
    }
    else{
        putPoison();
    }
}

void snakegame::showpoint()
{
    if(show){
        attron(COLOR_PAIR(9));
        move(2,maxwidth);
        printw("   YOUR SCORE  ");
        move(3,maxwidth);
        printw("   ------------");
        move(4,maxwidth);
        printw("   Point: \t %d",points);
        move(5,maxwidth);
        printw("   Food: \t %d",eatFood);
        move(6,maxwidth);
        printw("   Pois: \t %d",eatPoison);
        move(7,maxwidth);
        printw("   Size: \t %d",snakeLength);
        move(8,maxwidth);
        printw("   Gate: \t %d",0);

        move(11,maxwidth);
        printw("   MISSION%d  ",scorephase);
        move(12,maxwidth);
        printw("   ------------");
        move(13,maxwidth);
        if(!missionF)
            printw("   Food: \t %d/%d",eatFood, requiredFood);
        else{
            printw("   Food: \t (V)");
        }
        move(14,maxwidth);
        if(!missionP)
            printw("   Pois: \t %d/%d",eatPoison, requiredPoison);
        else{
            printw("   Pois: \t (V)");
        }
        move(15,maxwidth);
        if(!missionS)
            printw("   Size: \t %d/%d",snakeLength, requiredSize);
        else{
            printw("   Size: \t (V)");
        }
    }
}

bool snakegame::collision()
{
    for(int i=2;i<wall.size();i++){
        if(snake[0].x==wall[i].x &&snake[0].y==wall[i].y)
            return true;
    }
    for(int i=2;i<snake.size();i++){
        if(snake[0].x==snake[i].x &&snake[0].y==snake[i].y)
            return true;
    }
    if(snake[0].x==itemFood.x&&snake[0].y==itemFood.y){
        itemWhat=1;
        chooseItem();
        points+=15;
        snakeLength++;
        eatFood++;
        move(maxheight-1,0);
        showpoint();
        if((points%100)==0)
            del-=10000;
    }
    else if(snake[0].x==itemPoison.x&&snake[0].y==itemPoison.y){
        itemWhat=2;
        chooseItem();
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
        itemWhat = 0;
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
        if(direction!='d')
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
    if(itemWhat == 0)   // 아이템을 먹지 않았을 경우
    {
        move(snake[snake.size()-1].y,snake[snake.size()-1].x);
        attron(COLOR_PAIR(1));
        addch(' ');
        refresh();
        snake.pop_back();
    }
    if(itemWhat == 2){  // 독약을 먹었을 경우
        move(snake[snake.size()-1].y,snake[snake.size()-1].x);
        attron(COLOR_PAIR(1));
        addch(' ');
        refresh();
        snake.pop_back();
        move(snake[snake.size()-1].y,snake[snake.size()-1].x);
        attron(COLOR_PAIR(1));
        addch(' ');
        refresh();
        snake.pop_back();
    }
    if(itemCnt >= 80){      //일정시간이 지나면 자동으로 아이템 위치 변경
        move(itemMove.y, itemMove.x);
        attron(COLOR_PAIR(1));
        addch(' ');
        itemFood.x = 0;
        itemFood.y = 0;
        itemPoison.x = 0;
        itemPoison.y = 0;
        chooseItem();
    }
    missionCheck();
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
    attron(COLOR_PAIR(4));  //뱀머리
    addch(' ');
    move(snake[1].y,snake[1].x);
    attron(COLOR_PAIR(5));  //뱀몸통
    addch(' ');
    refresh();

}


void snakegame::map1(int y, int x){
    int snakeMap[x-1][y-1];
    wall.clear();
    snake.clear();
    // 뱀 좌표
    for(int i=0; i<x-1; i++){
        for(int j=0; j<y-1; j++){
			if(i == 0 || j ==0 || i == x-2 || j == y-2){
				snakeMap[i][j] = 1;
                wall.push_back(partpos(i,j));
			}
            else{
                snakeMap[i][j] = 0;
            }
		}
	}

	snakeMap[0][0] = 2;
	snakeMap[0][y-1] = 2;
	snakeMap[x-1][0] = 2;
	snakeMap[x-1][y-1] = 2;

    for(int i =0;i<5;i++)
        snake.push_back(partpos(maxwidth/2+i,maxheight/2));
    
    for(int i=0;i<snake.size();i++){
        attron(COLOR_PAIR(5));
        move(snake[i].y,snake[i].x);
        addch(' ');
    }

    for(int i=0; i<y-1; i++){
        for(int j=0; j<x-1; j++){
            attron(COLOR_PAIR(snakeMap[j][i]+1));
            move(i,j);
            addch(' ');
        }
    }

    eatFood = 0;
    eatPoison = 0;
    snakeLength =5;
    requiredFood = 5;
    requiredPoison = 2;
    requiredSize = 7;
    mission1 = true;
    mission2 = false;
    missionF = false;
    missionP = false;
    missionS = false;
    itemRandom = 1;
    itemCnt = 0;
    phase = 0;
    scorephase = 1;
    itemFood.x=0;
    itemFood.y=0;
    itemPoison.x=0;
    itemPoison.y=0;
    itemWhat = 0;
    direction='l';
    putFood();
    if(phase ==1){
        map1(maxheight,maxwidth);
    }
    move(maxheight-1,0);
    move(itemFood.y,itemFood.x);
    attron(COLOR_PAIR(6));  //음식
    addch(' ');
    showpoint();
    refresh();
}

void snakegame::map2(int y, int x){
    int snakeMap[x-1][y-1];
    wall.clear();   //벡터 초기화
    snake.clear();  //벡터 초기화
    // 벽 좌표 - 맵생성
    for(int i=0; i<x-1; i++){
        for(int j=0; j<y-1; j++){
			if(i == 0 || j ==0 || i == x-2 || j == y-2){
				snakeMap[i][j] = 1;
                wall.push_back(partpos(i,j));
			}
            else if( i == x/4 && j <= y/4){
                snakeMap[i][j] = 1;
                wall.push_back(partpos(i,j));
            }
            else if( i == 3*x/4 && j >= 3*y/4){
                snakeMap[i][j] = 1;
                wall.push_back(partpos(i,j));
            }
            else{
                snakeMap[i][j] = 0;
            }
		}
	}

    //가장자리
	snakeMap[0][0] = 2;
	snakeMap[0][y-1] = 2;
	snakeMap[x-1][0] = 2;
	snakeMap[x-1][y-1] = 2;
    snakeMap[x/4][0] = 2;
    snakeMap[3*x/4][y-1] = 2;

    for(int i=0; i<y-1; i++){
        for(int j=0; j<x-1; j++){
            attron(COLOR_PAIR(snakeMap[j][i]+1));
            move(i,j);
            addch(' ');
        }
    }

    for(int i =0;i<5;i++)
        snake.push_back(partpos(maxwidth/2+i,maxheight/2));
    
    for(int i=0;i<snake.size();i++){
        attron(COLOR_PAIR(5));
        move(snake[i].y,snake[i].x);
        addch(' ');
    }

    eatFood = 0;
    eatPoison = 0;
    snakeLength =5;
    requiredFood = 30;
    requiredPoison = 10;
    requiredSize = 20;
    mission1 = false;
    mission2 = true;
    missionF = false;
    missionP = false;
    missionS = false;
    itemRandom = 1;
    itemCnt = 0;
    phase = 0;
    scorephase = 2;
    itemFood.x=0;
    itemFood.y=0;
    itemPoison.x=0;
    itemPoison.y=0;
    itemWhat = 0;
    direction='l';  //초기 진행 방향
    putFood();
    if(phase ==1){
        map1(maxheight,maxwidth);
    }
    move(maxheight-1,0);
    move(itemFood.y,itemFood.x);
    attron(COLOR_PAIR(6));
    addch(' ');
    showpoint();
    refresh();

}

//미션 성공/진행 여부
void snakegame::missionCheck(){
    if(requiredFood == eatFood){
        missionF = true;
    }
    if(requiredPoison == eatPoison){
        missionP = true;
    }
    if(requiredSize == snakeLength){
        missionS = true;
    }
    if(missionF && missionP && missionS){
        points += 100;
        if(mission1){
            move(17,maxwidth);
            attron(COLOR_PAIR(11));
            printw("   Mission1 CLEAR!");
            phase = 2;
        }
        else if(mission2){
            move(18,maxwidth);
            attron(COLOR_PAIR(12));
            printw("   Mission2 CLEAR!");
        }
        return;
    }
}

//게임 오버 화면 출력
void snakegame::gameover(){
    int windowH;
    int windowW;
    getmaxyx(stdscr, windowH, windowW);

    for(int i=0; i<windowH; i++){
        for(int j=0; j<windowW; j++){
            attron(COLOR_PAIR(1));
            move(i,j);
            addch(' ');
        }
    }
    attron(COLOR_PAIR(10));
    move(maxheight/2,maxwidth/2);
    printw("game over");
    move(maxheight/2+3,maxwidth/2);
    printw("Point: %dp",points);
    attron(COLOR_PAIR(1));
    move(maxheight-2,maxwidth/2);
    printw("Press Any Button");
}

void snakegame::start()
{
    direction='u';
    while(1)
    {
        if(phase == 1){     //1단계 도입
            map1(maxheight,maxwidth);
        }
        if(phase == 2){     //2단계 도입
            map2(maxheight,maxwidth);
        }
        if(collision())
        {
            gameover();
            break;
        }
    movesnake();
    if(direction=='q')
        break;
    usleep(del);
    }
}