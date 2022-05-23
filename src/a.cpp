#include <ncurses.h>
#include <iostream>
#include <clocale>
#include "map.h"

using namespace std;


int main()
{
  initscr(); 
  resize_term(200, 200);
  //palette
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_YELLOW);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_WHITE);
  bkgd(COLOR_PAIR(3));
  
  WINDOW * main_window = newwin(40, 120, 0, 0);
  wbkgd(main_window, COLOR_PAIR(3));
  
  refresh();
 
  Map init;

  // setlocale(LC_ALL, "");  
  // Curses 모드 시작 start_color(); // Color 사용 선언 init_pair(1, COLOR_RED,COLOR_WHITE);


  //map size (22,22)




  //background color

  
  // mvprintw(1, 1, "Hello world");

  // attron(COLOR_PAIR(1));
  // border('|', '|', '-', '-', '*', '*', '*', '*');
  // mvprintw(5, 5, "Hello world");
  // attroff(COLOR_PAIR(1));

  //border

  
  // attron(COLOR_PAIR(2));
  // for (size_t i = 0; i < 60; i++)
  // {
  //   mvprintw(5, i, " ");
  // }
  // for (size_t i = 5; i < 65; i++)
  // {
  //   mvprintw(i, 0, " ");
  // }
  // attroff(COLOR_PAIR(2));

  //refresh

  getch();
  endwin();
  return 0; 
}