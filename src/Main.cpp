#include <ncurses.h>
#include <iostream>
#include <clocale>
#include <unistd.h>
#include "GameController.h"
using namespace std;

int main()
{
  //alarm handler
  // signal(SIGALRM, sig_alrm);
  srand((unsigned int)time(NULL));
  //init screen
  try
  {
    initscr();
  }
  catch(const std::exception& e)
  {
    cout << "cant start game!!" << endl;
    std::cerr << e.what() << '\n';
  }

  //keypad setting
  keypad(stdscr, TRUE);

  //cursor setting
  curs_set(0);
  noecho();

  //palette
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_YELLOW); // wall color
  init_pair(2, COLOR_RED, COLOR_BLACK); // game screen color
  init_pair(3, COLOR_BLACK, COLOR_WHITE); // background color
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // snake color

  //refresh background
  resize_term(1000, 1000);
  bkgd(COLOR_PAIR(2));
  refresh();

  // background window
  WINDOW *main_window;
  nodelay(stdscr, true);
  main_window = newwin(40, 125, 0, 0);
  wborder(main_window, '|', '|', '-', '-', '*', '*', '*', '*');
  wbkgd(main_window, COLOR_PAIR(3));
  wrefresh(main_window);

  // game setting
  GameController start;

  getch();
  endwin();
  return 0;
}
