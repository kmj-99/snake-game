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

  //refresh background
  resize_term(200, 200);
  refresh();

  //palette
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK); // wall color
  init_pair(2, COLOR_RED, COLOR_WHITE); // game screen color
  init_pair(3, COLOR_BLACK, COLOR_WHITE); // background color
  init_pair(4, COLOR_RED, COLOR_WHITE); // snake color
  init_pair(5,COLOR_BLUE,COLOR_WHITE);
  init_pair(6,COLOR_BLACK,COLOR_WHITE);


  // background window
  WINDOW *main_window;
  nodelay(stdscr, true);
  main_window = newwin(40, 125, 0, 0);
  // wborder(main_window, '|', '|', '-', '-', '*', '*', '*', '*');
  wbkgd(main_window, COLOR_PAIR(3));
  wrefresh(main_window);

  // game setting
  GameController start;


  Map m;
  int i=0;
  while(i!=-1){
    switch (i) {
      case 0:
          start.game_control(m.m1,i);
          break;
        case 1:
          start.game_control(m.m2,i);
          break;
        case 2:
          start.game_control(m.m3,i);
          break;
        case 3:
          start.game_control(m.m4,i);
          break;
        }


  }


  getch();
  endwin();

  return 0;
}
