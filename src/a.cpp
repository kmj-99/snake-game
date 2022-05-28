#include <ncurses.h>
#include <iostream>
#include <clocale>
#include <unistd.h>
#include <signal.h>
#include "map.h"
#include "snake.h"

#define UP 259
#define RIGHT 261
#define LEFT 260
#define DOWN 258

using namespace std;
void move();




void sig_alrm(int signum){
  //alarm
}
int inputSnakeWay();

int main()
{
  //alarm handler
  signal(SIGALRM, sig_alrm);

  //init screen
  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  resize_term(200, 200);
  refresh();

  //palette
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_YELLOW); // wall color
  init_pair(2, COLOR_RED, COLOR_BLACK); // game screen color
  init_pair(3, COLOR_BLACK, COLOR_WHITE); // background color
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // snake color

  // background window
  WINDOW *main_window;
  main_window = newwin(40, 125, 0, 0);
  wborder(main_window, '|', '|', '-', '-', '*', '*', '*', '*');
  wbkgd(main_window, COLOR_PAIR(3));
  wrefresh(main_window);

  // setting map
  Map init;

  Snake snake;
  while(1){
    int val;
    val=test.sense(inputSnakeWay());

    refresh();
  }



  getch();
  endwin();
  return 0;
}

//snake의 방향을 입력받는 함수
int inputSnakeWay(){
  keypad(stdscr,TRUE); // 입력 시 키보드 특수 키 입력을 가능하게 설정하는 함수 (ex- ESC,F!,F@,방향키..)
  curs_set(0); // 화면에 보이는 커서 설정 0 - 커서 사라짐 , 1- 일반커서 , 2- 큰 커서
  noecho(); // 입력한 값을 화면에 보이지 않게함
  int move = getch();
  return move;
}
