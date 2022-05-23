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


  getch();
  endwin();
  return 0;
}
