#include "BoardController.h"


BoardController::BoardController(){
  start_color();

  //set main board
  main_board = newwin(30, 60, 5, 10);
  wbkgd(main_board, COLOR_PAIR(2));

  //set score board
  score_board = newwin(15, 40, 5, 73);
  wbkgd(score_board, COLOR_PAIR(1));
  wattron(score_board, COLOR_PAIR(1));
  // wborder(score_board, '*', '*', '*', '*', '*', '*', '*', '*');
  mvwprintw(score_board, 0, 14, "Score Board");

  //set mission board
  mission_board = newwin(12, 40, 23, 73);
  wbkgd(mission_board, COLOR_PAIR(1));
  wattron(mission_board, COLOR_PAIR(1));
  // wborder(mission_board, '*', '*', '*', '*', '*', '*', '*', '*');
  mvwprintw(mission_board, 0, 14, "Mission Board");




}
