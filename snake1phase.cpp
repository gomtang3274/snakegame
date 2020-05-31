#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <time.h>
using namespace std;


int snakeMap[21][21] = {0,};
void snakeWhere(int x, int y){
    move(y, x);
}

void mapDrawing(){

    for(int i=0; i<21; i++){
        for(int j=0; j<21; j++){
            attron(COLOR_PAIR(snakeMap[i][j]+1));
            printw("  ");
        }
        printw("\n");
    }
}
int main(){

    // ncurses 기본설정
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    setlocale(LC_CTYPE, "ko_KR.utf-8");
    init_pair(1, COLOR_BLACK, COLOR_WHITE);  // Space 빈공간
    init_pair(2, COLOR_BLACK, COLOR_YELLOW); // Wall  벽
    init_pair(3, COLOR_BLACK, COLOR_YELLOW); // Immu  벽(게이트X) 
    init_pair(4, COLOR_BLACK, COLOR_CYAN);   // Head  뱀 머리
    init_pair(5, COLOR_BLACK, COLOR_GREEN);  // Body  뱀 몸통
    box(stdscr, 0, 0);
    attron(COLOR_PAIR(1));

    // 뱀 좌표
    for(int i=0; i<21; i++){
        for(int j=0; j<21; j++){
			if(i == 0 || j ==0 || i == 20 || j == 20){
				snakeMap[i][j] = 1;
			}
		}
	}

	snakeMap[0][0] = 2;
	snakeMap[0][20] = 2;
	snakeMap[20][0] = 2;
	snakeMap[20][20] = 2;

    

    // 스네이크 맵 출력
    mapDrawing();


    // 게임 진행
    bool playing = true;

    int curX = 10;
    int curY = 10;
    int kp;

    attron(COLOR_PAIR(1));
    move(curY,curX*2);
    printw("  ");


    for(int i=0; i<100; i++){
        kp = getch();
        snakeMap[curX][curY] = 0;
        switch(kp){
            case KEY_UP:
                curX -= 1;
                break;
            case KEY_DOWN:
                curX += 1;
                break;
            case KEY_LEFT:
                curY -= 1;
                break;
            case KEY_RIGHT:
                curY += 1;
                break;
            default:
                break;
        }
        snakeMap[curX][curY] = 4;
        clear();
        move(0,0);
        mapDrawing();
        move(curY, curX*2);
    }
    
    

    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(5));
    refresh();
    getch();
    endwin();
    return 0;
}

int snakeKey(int kp){
    int moving;
    switch(kp){
    case KEY_UP:
        moving = 0;
        break;
    case KEY_DOWN:
        moving = 1;
        break;
    case KEY_LEFT:
        moving = 2;
        break;
    case KEY_RIGHT:
        moving = 3;
        break;
    default:
        break;
    }
    return moving;
}
