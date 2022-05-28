#include "snake.h"


int Snake::sense(int move){

  switch(move)
  {
    case UP:
      return UP;

    case RIGHT:
      return RIGHT;

    case LEFT:
      return LEFT;

    case DOWN:
      return DOWN;
  }
  return 1;
}
