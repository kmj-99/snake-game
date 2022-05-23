#include <ncurses.h>
#include <iostream>
#include <clocale>
#include "map.h"

#define UP 259
#define RIGHT 261
#define LEFT 260
#define DOWN 258

using namespace std;

void move();

int main()
{
  initscr();
  resize_term(200, 200);
  //palette
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_YELLOW);
  init_pair(2, COLOR_RED, COLOR_BLACK); // background color
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  // bkgd(COLOR_PAIR(2));

  WINDOW *main_window;
  main_window = newwin(40, 125, 0, 0);
  wborder(main_window, '|', '|', '-', '-', '*', '*', '*', '*');
  wbkgd(main_window, COLOR_PAIR(3));


  refresh();
  wrefresh(main_window);
  Map init;




while(1){
  move();

  refresh();
}



  getch();
  endwin();
  return 0;
}



void move(){
  keypad(stdscr,TRUE); // 입력 시 키보드 특수 키 입력을 가능하게 설정하는 함수 (ex- ESC,F!,F@,방향키..)
  curs_set(0); // 화면에 보이는 커서 설정 0 - 커서 사라짐 , 1- 일반커서 , 2- 큰 커서
  noecho(); // 입력한 값을 화면에 보이지 않게함

	int move = getch();
	switch(move)
	{
		case UP:
      printw("UP");
			break;
		case RIGHT:
      printw("RIGHT");
			break;
		case LEFT:
      printw("LEFT");
			break;
		case DOWN:
      printw("DOWN");
			break;
		case KEY_BACKSPACE:
      printw("oh ho");
			break;
	}

}
