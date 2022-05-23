#include <ncurses.h>
#include <iostream>
#include <clocale>
#include <unistd.h>
#include <signal.h>
#include "map.h"

using namespace std;

void sig_alrm(int signum){
  //alarm
}

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


  getch();
  endwin();
  return 0;
}

