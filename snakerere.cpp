#include "snakere.h"

wall::wall(int col, int row, char op){
    x=col;
    y=row;
    open = op;
}
wall::wall(){
    x=y=0;
    open='a';
}

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
    gameOn = true;
    stage = 1;      // 1단계
    points= 0;      //점수
    del=110000;
    srand(time(0)); // 변수고정
    //초기화
}
snakegame::~snakegame()
{
    nodelay(stdscr,false);
    getch();
    endwin();
}

void snakegame::makeMap(int stage){
    int row,column;
    if(stage==1)
    {
        eatFood = 0;
        eatPoison = 0;
        snakeLength =3;
        requiredSize = 7;
        requiredFood = 4;
        requiredPoison = 3;
        requiredGate = 1;
        direction = 'u';
        snakebody.push_back(partpos(15, 18));
        snakebody.push_back(partpos(16, 18));
        snakebody.push_back(partpos(17, 18));
        gameMap[0] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";
        gameMap[1] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[2] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[3] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[4] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[5] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[6] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[7] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[8] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[9] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[10] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[11] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[12] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[13] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[14] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[15] = "wbbbbbbbbbbbbbbbbbSbbbbbbbbbbw";
        gameMap[16] = "wbbbbbbbbbbbbbbbbbsbbbbbbbbbbw";
        gameMap[17] = "wbbbbbbbbbbbbbbbbbsbbbbbbbbbbw";
        gameMap[18] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[19] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[20] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[21] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[22] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[23] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[24] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[25] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[26] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[27] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[28] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[29] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";

        walls.clear();
        walls.reserve(112);
        for(column=1;column<29;column++){
            walls.push_back(wall(0,column,'d'));
        }
        for(column=1;column<29;column++){
            walls.push_back(wall(29,column,'u'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,0,'r'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,29,'l'));
        }
    }
    if(stage == 2)
    {

        requiredSize = 7;
        requiredFood = 4;
        requiredPoison = 3;
        requiredGate = 1;
        direction = 'l';
        snakebody.push_back(partpos(12, 15));
        snakebody.push_back(partpos(12, 16));
        snakebody.push_back(partpos(12, 17));
        snakebody.push_back(partpos(12, 18));
        gameMap[0] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";
        gameMap[1] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[2] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[3] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[4] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[5] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[6] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[7] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[8] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[9] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[10] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[11] = "wbbbbbbbbwbbbbbSsssbbbbbbbbbbw";
        gameMap[12] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[13] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[14] = "wbbbbbbbbwbbbbbbbbbbbbbbbbbbbw";
        gameMap[15] = "wbbbbbbbbwwwwwwwwwwwbbbbbbbbbw";
        gameMap[16] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[17] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[18] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[19] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[20] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[21] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[22] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[23] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[24] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[25] = "wbbbbbbbbbbbbbbbbbbwbbbbbbbbbw";
        gameMap[26] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[27] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[28] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[29] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";

        walls.clear();
        walls.reserve(143);
        for(column=1;column<29;column++){
            walls.push_back(wall(0,column,'d'));
        }
        for(column=1;column<29;column++){
            walls.push_back(wall(29,column,'u'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,0,'r'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,29,'l'));
        }
        walls.push_back(wall(5, 9, 'n'));
        walls.push_back(wall(6, 9, 'h'));
        walls.push_back(wall(7, 9, 'h'));
        walls.push_back(wall(8, 9, 'h'));
        walls.push_back(wall(9, 9, 'h'));
        walls.push_back(wall(10, 9, 'h'));
        walls.push_back(wall(11, 9, 'h'));
        walls.push_back(wall(12, 9, 'h'));
        walls.push_back(wall(13, 9, 'h'));
        walls.push_back(wall(14, 9, 'h'));
        walls.push_back(wall(15, 9, '3'));
        walls.push_back(wall(15, 10, 'v'));
        walls.push_back(wall(15, 11, 'v'));
        walls.push_back(wall(15, 12, 'v'));
        walls.push_back(wall(15, 13, 'v'));
        walls.push_back(wall(15, 14, 'v'));
        walls.push_back(wall(15, 15, 'v'));
        walls.push_back(wall(15, 16, 'v'));
        walls.push_back(wall(15, 17, 'v'));
        walls.push_back(wall(15, 18, 'v'));
        walls.push_back(wall(15, 19, '1'));
        walls.push_back(wall(16, 19, 'h'));
        walls.push_back(wall(17, 19, 'h'));
        walls.push_back(wall(18, 19, 'h'));
        walls.push_back(wall(19, 19, 'h'));
        walls.push_back(wall(20, 19, 'h'));
        walls.push_back(wall(21, 19, 'h'));
        walls.push_back(wall(22, 19, 'h'));
        walls.push_back(wall(23, 19, 'h'));
        walls.push_back(wall(24, 19, 'h'));
        walls.push_back(wall(25, 19, 's'));
    }
    if(stage == 3)
    {
        requiredSize = 7;
        requiredFood = 4;
        requiredPoison = 3;
        requiredGate = 1;
        direction = 'u';
        snakebody.push_back(partpos(14, 14));
        snakebody.push_back(partpos(15, 14));
        snakebody.push_back(partpos(15, 15));
        snakebody.push_back(partpos(14, 15));
        gameMap[0] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";
        gameMap[1] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[2] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[3] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[4] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[5] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[6] = "wbbbbbwwwwwwbbbbbbwwwwwwbbbbbw";
        gameMap[7] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[8] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[9] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[10] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[11] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[12] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[13] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[14] = "wbbbbbbbbbbbbbSsbbbbbbbbbbbbbw";
        gameMap[15] = "wbbbbbbbbbbbbbssbbbbbbbbbbbbbw";
        gameMap[16] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[17] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[18] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[19] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[20] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[21] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[22] = "wbbbbbwbbbbbbbbbbbbbbbbwbbbbbw";
        gameMap[23] = "wbbbbbwwwwwwbbbbbbwwwwwwbbbbbw";
        gameMap[24] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[25] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[26] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[27] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[28] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[29] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";

        walls.clear();
        walls.reserve(156);
        for(column=1;column<29;column++){
            walls.push_back(wall(0,column,'d'));
        }
        for(column=1;column<29;column++){
            walls.push_back(wall(29,column,'u'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,0,'r'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,29,'l'));
        }
        walls.push_back(wall(6, 6, '2'));
        walls.push_back(wall(6, 7, 'v'));
        walls.push_back(wall(6, 8, 'v'));
        walls.push_back(wall(6, 9, 'v'));
        walls.push_back(wall(6, 10, 'v'));
        walls.push_back(wall(6, 11, 'e'));
        walls.push_back(wall(7, 6, 'h'));
        walls.push_back(wall(8, 6, 'h'));
        walls.push_back(wall(9, 6, 'h'));
        walls.push_back(wall(10, 6, 'h'));
        walls.push_back(wall(11, 6, 's'));
        walls.push_back(wall(6, 18, 'w'));
        walls.push_back(wall(6, 19, 'v'));
        walls.push_back(wall(6, 20, 'v'));
        walls.push_back(wall(6, 21, 'v'));
        walls.push_back(wall(6, 22, 'v'));
        walls.push_back(wall(6, 23, '1'));
        walls.push_back(wall(7, 23, 'h'));
        walls.push_back(wall(8, 23, 'h'));
        walls.push_back(wall(9, 23, 'h'));
        walls.push_back(wall(10, 23, 'h'));
        walls.push_back(wall(11, 23, 's'));
        walls.push_back(wall(18, 6, 'n'));
        walls.push_back(wall(19, 6, 'h'));
        walls.push_back(wall(20, 6, 'h'));
        walls.push_back(wall(21, 6, 'h'));
        walls.push_back(wall(22, 6, 'h'));
        walls.push_back(wall(23, 6, '3'));
        walls.push_back(wall(23, 7, 'v'));
        walls.push_back(wall(23, 8, 'v'));
        walls.push_back(wall(23, 9, 'v'));
        walls.push_back(wall(23, 10, 'v'));
        walls.push_back(wall(23, 11, 'e'));
        walls.push_back(wall(18, 23, 'n'));
        walls.push_back(wall(19, 23, 'h'));
        walls.push_back(wall(20, 23, 'h'));
        walls.push_back(wall(21, 23, 'h'));
        walls.push_back(wall(22, 23, 'h'));
        walls.push_back(wall(23, 18, 'w'));
        walls.push_back(wall(23, 19, 'v'));
        walls.push_back(wall(23, 20, 'v'));
        walls.push_back(wall(23, 21, 'v'));
        walls.push_back(wall(23, 22, 'v'));
        walls.push_back(wall(23, 23, '4'));        
        
    }
    if(stage == 4)
    {

        requiredSize = 30;
        requiredFood = 0;
        requiredPoison = 0;
        requiredGate = 5;
        direction = 'l';
        snakebody.push_back(partpos(16, 17));
        snakebody.push_back(partpos(16, 18));
        snakebody.push_back(partpos(16, 19));
        snakebody.push_back(partpos(16, 20));
        snakebody.push_back(partpos(16, 21));
        snakebody.push_back(partpos(16, 22));
        snakebody.push_back(partpos(16, 23));
        snakebody.push_back(partpos(16, 24));
        snakebody.push_back(partpos(16, 25));
        snakebody.push_back(partpos(16, 26));
        snakebody.push_back(partpos(16, 27));
        snakebody.push_back(partpos(15, 27));
        snakebody.push_back(partpos(14, 27));
        snakebody.push_back(partpos(14, 26));
        snakebody.push_back(partpos(14, 25));
        snakebody.push_back(partpos(14, 24));
        snakebody.push_back(partpos(14, 23));
        snakebody.push_back(partpos(14, 22));
        snakebody.push_back(partpos(14, 21));
        snakebody.push_back(partpos(14, 20));
        snakebody.push_back(partpos(14, 19));
        snakebody.push_back(partpos(14, 18));
        snakebody.push_back(partpos(14, 17));
        snakebody.push_back(partpos(14, 16));
        snakebody.push_back(partpos(14, 15));
        snakebody.push_back(partpos(13, 15));
        snakebody.push_back(partpos(12, 15));
        snakebody.push_back(partpos(11, 15));
        snakebody.push_back(partpos(10, 15));
        snakebody.push_back(partpos(9, 15));
        snakebody.push_back(partpos(8, 15));
        snakebody.push_back(partpos(7, 15));
        snakebody.push_back(partpos(6, 15));
        snakebody.push_back(partpos(5, 15));
        snakebody.push_back(partpos(4, 15));
        snakebody.push_back(partpos(3, 15));
        snakebody.push_back(partpos(2, 15));
        snakebody.push_back(partpos(2, 14));
        snakebody.push_back(partpos(2, 13));
        snakebody.push_back(partpos(3, 13));
        snakebody.push_back(partpos(4, 13));
        snakebody.push_back(partpos(5, 13));
        snakebody.push_back(partpos(6, 13));
        snakebody.push_back(partpos(7, 13));
        snakebody.push_back(partpos(8, 13));
        snakebody.push_back(partpos(9, 13));
        snakebody.push_back(partpos(10, 13));
        snakebody.push_back(partpos(11, 13));
        snakebody.push_back(partpos(12, 13));
        gameMap[0] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";
        gameMap[1] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[2] = "wbbbbbbbbbbbbsssbbbbbbbbbbbbbw";
        gameMap[3] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[4] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[5] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[6] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[7] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[8] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[9] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[10] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[11] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[12] = "wbbbbbbbbbbbbswsbbbbbbbbbbbbbw";
        gameMap[13] = "wbbbbbbbbbbbbbbsbbbbbbbbbbbbbw";
        gameMap[14] = "wbbbbbbbbbbbbbbsssssssssssssbw";
        gameMap[15] = "wbbwwwwwwwwwbbwbbwwwwwwwwwwsbw";
        gameMap[16] = "wbbbbbbbbbbbbbbbbSssssssssssbw";
        gameMap[17] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[18] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[19] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[20] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[21] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[22] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[23] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[24] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[25] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[26] = "wbbbbbbbbbbbbbwbbbbbbbbbbbbbbw";
        gameMap[27] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[28] = "wbbbbbbbbbbbbbbbbbbbbbbbbbbbbw";
        gameMap[29] = "WwwwwwwwwwwwwwwwwwwwwwwwwwwwwW";

        walls.clear();
        walls.reserve(151);
        for(column=1;column<29;column++){
            walls.push_back(wall(0,column,'d'));
        }
        for(column=1;column<29;column++){
            walls.push_back(wall(29,column,'u'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,0,'r'));
        }
        for(row=1;row<29;row++){
            walls.push_back(wall(row,29,'l'));
        }
        walls.push_back(wall(15, 14, 'a'));
        walls.push_back(wall(3, 14, 'n'));
        walls.push_back(wall(4, 14, 'h'));
        walls.push_back(wall(5, 14, 'h'));
        walls.push_back(wall(6, 14, 'h'));
        walls.push_back(wall(7, 14, 'h'));
        walls.push_back(wall(8, 14, 'h'));
        walls.push_back(wall(9, 14, 'h'));
        walls.push_back(wall(10, 14, 'h'));
        walls.push_back(wall(11, 14, 'h'));
        walls.push_back(wall(12, 14, 's'));
        walls.push_back(wall(18, 14, 'n'));
        walls.push_back(wall(19, 14, 'h'));
        walls.push_back(wall(20, 14, 'h'));
        walls.push_back(wall(21, 14, 'h'));
        walls.push_back(wall(22, 14, 'h'));
        walls.push_back(wall(23, 14, 'h'));
        walls.push_back(wall(24, 14, 'h'));
        walls.push_back(wall(25, 14, 'h'));
        walls.push_back(wall(26, 14, 's'));
        walls.push_back(wall(15, 3, 'w'));
        walls.push_back(wall(15, 4, 'v'));
        walls.push_back(wall(15, 5, 'v'));
        walls.push_back(wall(15, 6, 'v'));
        walls.push_back(wall(15, 7, 'v'));
        walls.push_back(wall(15, 8, 'v'));
        walls.push_back(wall(15, 9, 'v'));
        walls.push_back(wall(15, 10, 'v'));
        walls.push_back(wall(15, 11, 'e'));
        walls.push_back(wall(15, 17, 'w'));
        walls.push_back(wall(15, 18, 'v'));
        walls.push_back(wall(15, 19, 'v'));
        walls.push_back(wall(15, 20, 'v'));
        walls.push_back(wall(15, 21, 'v'));
        walls.push_back(wall(15, 22, 'v'));
        walls.push_back(wall(15, 23, 'v'));
        walls.push_back(wall(15, 24, 'v'));
        walls.push_back(wall(15, 25, 'v'));
        walls.push_back(wall(15, 26, 'e'));
    }
    for(row = 0;row<30;row++){
        for(column=0;column<30;column++){
            move(row,column);
            switch (gameMap[row][column])
            {
            case 'b':
                attron(COLOR_PAIR(1));
                break;
            case 'w':
                attron(COLOR_PAIR(2));
                break;
            case 'W':
                attron(COLOR_PAIR(3));
                break;
            case 'S':
                attron(COLOR_PAIR(4));
                break;
            case 's':
                attron(COLOR_PAIR(5));
                break;
            }
            addch(' ');
        }
    }
    missionF = false;
    missionP = false;
    missionS = false;
    missionG = false;
    gameSuccess = false;
    foodTime = poisonTime =gateTimer= gateTime= gameTime =itemCnt = 0;
    itemWhat = 0;
    fExist = false;
    pExist = false;
    gExist = false;
    inGate = false;
    startGate = false;

}

void snakegame::gameover(){
    flushinp();
    nodelay(stdscr,false);
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
    if(gameSuccess){
        //다음 스테이지로 이어갈 지 물어보기
        
        attron(COLOR_PAIR(10));
        move(windowH/2,windowW/2);
        printw("game over");
        move(windowH/2+3,windowW/2);
        printw("Point: %dp",points);
        attron(COLOR_PAIR(1));
        move(windowH-2,windowW/2);
        printw("Press q to stop else to succeed");
        char weather = getch();
        if(weather = 'q'){
            gameOn = false;
        }
        else{
            stage++;
        }
    }
    else{
        //게임 다시 할지 물어보기
        attron(COLOR_PAIR(10));
        move(windowH/2,windowW/2);
        printw("game over");
        move(windowH/2+3,windowW/2);
        printw("Point: %dp",points);
        attron(COLOR_PAIR(1));
        move(windowH-2,windowW/2);
        printw("Press q to stop else to try again");
        char weather = getch();
        if(weather='q'){
            gameOn = false;
        }
    }
    nodelay(stdscr,true);
}

void snakegame::start()
{
    while(gameOn)
    {
        makeMap(stage);
        
        while(1)
        {
            
            if(collision() || gameSuccess)//collision에서 모든 충돌을 다룸
            {
                gameover();//성공 시 화면과 실패시 화면이 다르고 설정이 달라짐. 공통적으로 더 할지 물어보고 on을 바꿔줌
                break;
            }
            movesnake();
            if(direction=='q')
                break;
            flushinp();//키를 연속해서 누를경우 큐에 과하게 쌓이는걸 방지하기 위함
            usleep(del);
        }
        
    }
    
}

bool snakegame::collision(){
    int moveX=0,moveY=0;
    if(direction=='l') moveX=-1;
    else if (direction=='r') moveX=1;
    else if (direction=='u') moveY=-1;
    else if (direction=='d') moveY=1;

    if(gameMap[snakebody[0].y+moveY][snakebody[0].x+moveX]=='w'||gameMap[snakebody[0].y+moveY][snakebody[0].x+moveX]=='s')
        return true;
    else if(gameMap[snakebody[0].y+moveY][snakebody[0].x+moveX]=='g'){
        itemWhat=1;
        chooseItem();
        points+=15;
        snakeLength++;
        eatFood++;
        move(gameHeight-1,0);
        showpoint();
    }
    else if(gameMap[snakebody[0].y+moveY][snakebody[0].x+moveX]=='p'){
        itemWhat=2;
        chooseItem();
        points+=10;
        snakeLength--;
        eatPoison++;
        move(gameHeight-1,0);
        showpoint();
        if(snakebody.size() <= 3){
            move(snakebody[snakebody.size()-1].y,snakebody[snakebody.size()-1].x);
            addch(' ');
            refresh();
            snakebody.pop_back();
            return true;
        }
    }
    else if(gameMap[snakebody[0].y+moveY][snakebody[0].x+moveX]=='q'){
        itemWhat = 3;
        inGate = true;
        gatePoints++;
    }
    else if(gameMap[snakebody[0].y+moveY][snakebody[0].x+moveX]=='Q'){
        itemWhat = 4;
        inGate = true;
        gatePoints++;
    }
    else
    {
        itemWhat = 0;
    }
    return false;
}

void snakegame::movesnake(){
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
        move(snakebody[snakebody.size()-1].y,snakebody[snakebody.size()-1].x);
        gameMap[snakebody[snakebody.size()-1].y][snakebody[snakebody.size()-1].x]='b';
        attron(COLOR_PAIR(1));
        addch(' ');
        refresh();
        snakebody.pop_back();
    }
    if(itemWhat == 2){  // 독약을 먹었을 경우
        move(snakebody[snakebody.size()-1].y,snakebody[snakebody.size()-1].x);
        gameMap[snakebody[snakebody.size()-1].y][snakebody[snakebody.size()-1].x]='b';
        attron(COLOR_PAIR(1));
        addch(' ');
        refresh();
        snakebody.pop_back();
        move(snakebody[snakebody.size()-1].y,snakebody[snakebody.size()-1].x);
        gameMap[snakebody[snakebody.size()-1].y][snakebody[snakebody.size()-1].x]='b';
        attron(COLOR_PAIR(1));
        addch(' ');
        refresh();
        snakebody.pop_back();
    }
    // if(itemCnt >= 80){      //일정시간이 지나면 자동으로 아이템 위치 변경
    //     move(itemMove.y, itemMove.x);
    //     attron(COLOR_PAIR(1));
    //     addch(' ');
    //     itemFood.x = 0;
    //     itemFood.y = 0;
    //     itemPoison.x = 0;
    //     itemPoison.y = 0;
    //     chooseItem();
    // }
    missionCheck();
    //관문1->관문2
    if(itemWhat == 3){
        switch (gate2.open)
        {
        case 'n':
            if(direction=='d')
                direction='l';
            break;
        
        case 'e':
            if(direction=='l')
                direction='u';
            break;
        case 's':
            if(direction=='u')
                direction='r';
            break;
        case 'w':
            if(direction=='r')
                direction='d';
            break;
        case 'h':
            if(direction=='r')
                direction='d';
            else if(direction=='l')
                direction='u';
            break;
        case 'v':
            if(direction=='d')
                direction='l';
            else if(direction=='u')
                direction='r';
            break;
        case '1':
            if(direction=='d')
                direction='r';
            else if(direction=='l')
                direction='u';
            break;
        case '2':
            if(direction=='d')
                direction='l';
            else if(direction=='r')
                direction='u';
            break;
        case '3':
            if(direction=='u')
                direction='l';
            else if(direction=='r')
                direction='d';
            break;
        case '4':
            if(direction=='u')
                direction='r';
            else if(direction=='l')
                direction='d';
            break;
        case 'r':
            direction = 'r';
            break;
        case 'l':
            direction = 'l';
            break;
        case 'u':
            direction = 'u';
            break;
        case 'd':
            direction = 'd';
            break;
        }
        if(direction=='l'){
            snakebody.push_front(partpos(gate2.x-1,gate2.y));
        }
        else if (direction=='r'){
            snakebody.push_front(partpos(gate2.x+1,gate2.y));
        }
        else if (direction=='u'){
            snakebody.push_front(partpos(gate2.x,gate2.y-1));
        }
        else if (direction=='d'){
            snakebody.push_front(partpos(gate2.x,gate2.y+1));
        }
    }
    //관문2->관문1
    else if(itemWhat ==4){
        switch (gate1.open)
        {
        case 'n':
            if(direction=='d')
                direction='l';
            break;
        
        case 'e':
            if(direction=='l')
                direction='u';
            break;
        case 's':
            if(direction=='u')
                direction='r';
            break;
        case 'w':
            if(direction=='r')
                direction='d';
            break;
        case 'h':
            if(direction=='r')
                direction='d';
            else if(direction=='l')
                direction='u';
            break;
        case 'v':
            if(direction=='d')
                direction='l';
            else if(direction=='u')
                direction='r';
            break;
        case '1':
            if(direction=='d')
                direction='r';
            else if(direction=='l')
                direction='u';
            break;
        case '2':
            if(direction=='d')
                direction='l';
            else if(direction=='r')
                direction='u';
            break;
        case '3':
            if(direction=='u')
                direction='l';
            else if(direction=='r')
                direction='d';
            break;
        case '4':
            if(direction=='u')
                direction='r';
            else if(direction=='l')
                direction='d';
            break;
        case 'r':
            direction = 'r';
            break;
        case 'l':
            direction = 'l';
            break;
        case 'u':
            direction = 'u';
            break;
        case 'd':
            direction = 'd';
            break;
        }
        if(direction=='l'){
            snakebody.push_front(partpos(gate1.x-1,gate1.y));
        }
        else if (direction=='r'){
            snakebody.push_front(partpos(gate1.x+1,gate1.y));
        }
        else if (direction=='u'){
            snakebody.push_front(partpos(gate1.x,gate1.y-1));
        }
        else if (direction=='d'){
            snakebody.push_front(partpos(gate1.x,gate1.y+1));
        }
    }
    else{
        if(direction=='l'){
            snakebody.push_front(partpos(snakebody[0].x-1,snakebody[0].y));
        }
        else if (direction=='r'){
            snakebody.push_front(partpos(snakebody[0].x+1,snakebody[0].y));
        }
        else if (direction=='u'){
            snakebody.push_front(partpos(snakebody[0].x,snakebody[0].y-1));
        }
        else if (direction=='d'){
            snakebody.push_front(partpos(snakebody[0].x,snakebody[0].y+1));
        }
    }
    if(fExist)
    {
        if(foodTime<80)
        {
            foodTime++;
        }
        else
        {
            gameMap[itemFood.y][itemFood.x]='b';
            move(itemFood.y,itemFood.x);
            attron(COLOR_PAIR(1));
            addch(' ');
            putFood();
        }
        
    }
    else
    {
        putFood();
    }
    if(pExist)
    {
        if(poisonTime<80)
        {
            poisonTime++;
        }
        else
        {
            gameMap[itemPoison.y][itemPoison.x]='b';
            move(itemPoison.y,itemPoison.x);
            attron(COLOR_PAIR(1));
            addch(' ');
            putPoison();
        }
        
    }
    else
    {
        putPoison();
    }
    if(startGate)
    {
        if(!gExist)
        {
            putGate();
        }
    }
    else
    {
        gateTime++;
        if(gateTime>30)
            startGate=true;
    }
    
    
    if(inGate)
    {
        if(gateTimer<snakebody.size())
            gateTimer++;
        else
        {
            gameMap[gate1.y][gate1.x]='w';
            gameMap[gate2.y][gate2.x]='w';
            gateTimer=0;
            attron(COLOR_PAIR(2));
            move(gate1.y,gate1.x);
            addch(' ');
            move(gate1.y,gate1.x);
            addch(' ');
            putGate();
        }
        
    }
    
    
    move(snakebody[0].y,snakebody[0].x);
    gameMap[snakebody[0].y][snakebody[0].x]='S';
    attron(COLOR_PAIR(4));  //뱀머리
    addch(' ');
    move(snakebody[1].y,snakebody[1].x);
    gameMap[snakebody[1].y][snakebody[1].x]='s';
    attron(COLOR_PAIR(5));  //뱀몸통
    addch(' ');
    refresh();
}
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
    if(requiredGate == gatePoints){
        missionG=true;
    }
    if(missionF && missionP && missionS && missionG){
        points += 100;
        gameSuccess = true;
        return;
    }
}
//아이템 - 음식
void snakegame::putFood()
{
    int tmpx=rand()%gameWidth;
    int tmpy=rand()%gameHeight;
    while(gameMap[tmpy][tmpx]!='b')
    {
        tmpx=rand()%gameWidth;
        tmpy=rand()%gameHeight;
    }
    gameMap[tmpy][tmpx]='g';
    fExist = true;
    //아이템위치설정
    itemFood.x=tmpx;
    itemFood.y=tmpy;
    itemMove.x=tmpx;
    itemMove.y=tmpy;
        
    move(itemFood.y,itemFood.x);
    attron(COLOR_PAIR(6));
    addch(' ');
    refresh();
}

void snakegame::putPoison()
{
    int tmpx=rand()%gameWidth;
    int tmpy=rand()%gameHeight;
    while(gameMap[tmpy][tmpx]!='b')
    {
        tmpx=rand()%gameWidth;
        tmpy=rand()%gameHeight;
    }
    gameMap[tmpy][tmpx]='p';
    pExist = true;

    itemPoison.x=tmpx;
    itemPoison.y=tmpy;
    itemMove.x=tmpx;
    itemMove.y=tmpy;
    move(itemPoison.y,itemPoison.x);
    attron(COLOR_PAIR(7)); //독
    addch(' ');
    refresh();
}
void snakegame::putGate()
{
    int gate1idx = rand()%walls.size();
    int gate2idx = rand()%walls.size();
    while(gate1idx!=gate2idx)
        gate2idx = rand()%walls.size();
    
    gate1=wall(walls[gate1idx].x,walls[gate1idx].y,walls[gate1idx].open);
    gate2=wall(walls[gate2idx].x,walls[gate2idx].y,walls[gate2idx].open);
    gameMap[gate1.y][gate1.x]='q';
    gameMap[gate2.y][gate2.x]='Q';
    gExist = true;

    attron(COLOR_PAIR(8));
    move(gate1.y,gate1.x);
    addch(' ');
    move(gate2.y,gate2.x);
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
        move(2,gameWidth);
        printw("   YOUR SCORE  ");
        move(3,gameWidth);
        printw("   ------------");
        move(4,gameWidth);
        printw("   Point: \t %d",points);
        move(5,gameWidth);
        printw("   Food: \t %d",eatFood);
        move(6,gameWidth);
        printw("   Pois: \t %d",eatPoison);
        move(7,gameWidth);
        printw("   Size: \t %d",snakeLength);
        move(8,gameWidth);
        printw("   Gate: \t %d",gatePoints);

        move(11,gameWidth);
        printw("   MISSION%d  ",scorephase);
        move(12,gameWidth);
        printw("   ------------");
        move(13,gameWidth);
        if(!missionF)
            printw("   Food: \t %d/%d",eatFood, requiredFood);
        else{
            printw("   Food: \t (V)");
        }
        move(14,gameWidth);
        if(!missionP)
            printw("   Pois: \t %d/%d",eatPoison, requiredPoison);
        else{
            printw("   Pois: \t (V)");
        }
        move(15,gameWidth);
        if(!missionS)
            printw("   Size: \t %d/%d",snakeLength, requiredSize);
        else{
            printw("   Size: \t (V)");
        }
        move(16,gameWidth);
        if(!missionG)
            printw("   Gate: \t %d/%d",gatePoints, goalGate);
        else{
            printw("   Gate: \t (V)");
        }
        move(17,gameWidth);
        printw("   time: \t %d",gameTime/10);
    }
}