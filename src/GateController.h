#include "Map.h"
#include <cstdlib>
#include <ctime>
#define UP 259
#define RIGHT 261
#define LEFT 260
#define DOWN 258
using namespace std;


class Gate{
    public:
        Map& gateMap;
        Snake& snake;
        int& command;
        int& gateCount;
        Gate(Map& map,Snake& snake,int& command,int& gateCount) : gateMap(map) ,snake(snake),command(command),gateCount(gateCount){};
        int x=-1,y=-1;
        int x2=-1, y2=-1;
        int gateX1=-1,gateY1=-1,gateX2=-1,gateY2=-1;
        int x_border=-1 , y_border=-1;
        int x_border_left=-1, x_border_right=-1,y_border_up=-1 , y_border_down=-1;
        int x_same_border=0,y_same_border=0;
        int shape=0;

        void gateRefresh(){
          x_border=-1;
          y_border=-1;
          shape=0;
          x=-1; y=-1; gateX1=-1; gateX2=-1; gateY1=-1; gateY2=-1;
          x_border_left=-1; x_border_right=-1;
          y_border_up=-1; y_border_down=-1;
          x_same_border=-1; y_same_border=-1;


          srand((unsigned int)time(NULL));

          switch(shape){
            case 0: // x_border , x_border
              x_border_left=rand()%2;
              x_border_right=rand()%2;
              if(x_border_left==x_border_right){
                x_same_border=1;
                x=rand() % 28 + 1;
                x2=rand() % 28 + 1;
                while(x==x2){
                  x=rand()%2;
                  x2=rand()%2;
                }
                // left x_border와 right x_border를 랜덤으로 선택
                if(x%2==0){
                  gateMap.m[x][0] = 10;
                  gateMap.m[x2][0] = 10;
                  gateX1=x; gateY1=0;
                  gateX2=x2; gateY2=0;
                }else{
                  gateMap.m[x][59] = 10;
                  gateMap.m[x2][59] = 10;
                  gateX1=x; gateY1=59;
                  gateX2=x2; gateY2=59;
                }

              }else{
                x_same_border=0;
                x=rand()%28 + 1;
                x2=rand()%28 + 1;
                gateMap.m[x][0]=10;
                gateMap.m[x2][59]=10;
                gateX1=x; gateY1=0;
                gateX2=x2; gateY2=59;
              }

              break;
            case 1: // y_border , y_border
              y_border_up=rand()%2;
              y_border_down=rand()%2;
              if(y_border_up==y_border_down){
                y_same_border=1;
                y=rand()%58 + 1;
                y2=rand()%58 + 1;
                while(y==y2){
                  y=rand()%58 + 1;
                  y2=rand()%58 + 1;
                }

                if(y%2==0){
                  gateMap.m[0][y]=10;
                  gateMap.m[0][y2]=10;
                  gateX1=0; gateY1=y;
                  gateX2=0; gateY2=y2;
                }else{
                  gateMap.m[29][y]=10;
                  gateMap.m[29][y2]=10;
                  gateX1=29; gateY1=y;
                  gateX2=29; gateY2=y2;
                }

              }else{
                y_same_border=0;
                y=rand()%58 + 1;
                y2=rand()%58 + 1;
                gateMap.m[0][y]=10;
                gateMap.m[29][y2]=10;
                gateX1=0; gateY1=y;
                gateX2=29; gateY2=y2;
              }
              break;
            case 2: // x_border , y_border
              x = rand() % 28 + 1;
              y = rand() % 58 + 1;

              srand((unsigned int)time(NULL));
              x_border = rand() % 2;

              srand((unsigned int)time(NULL));
              y_border = rand() % 2;

              if(x_border == 0) {
                gateMap.m[x][0] = 10;
                gateX1=x; gateY1=0;
              }
              else if(x_border == 1) {
                gateMap.m[x][59] = 10;
                gateX1=x; gateY1=59;
              }

              if(y_border == 0) {
                gateMap.m[0][y] = 10;
                gateX2=0; gateY2=y;
              }
              else if(y_border == 1) {
                gateMap.m[29][y] = 10;
                gateX2=29; gateY2=y;
              }

              break;

          };


        }


        // gate를 감지해서 통과하게 만다는 함수
        void gateSensor(){
          switch(shape){ // gate의 유형에 따라 다른 로직구현
            case 0: // x_line , x_line
              if(snake.body[0][1]==0){ // 왼쪽 gate로 갈때
                if(snake.body[0][0]==gateX1){ // gateX1로 들어갈 때
                  snake.body[0][0]=gateX2;
                  gateCount=-10;
                  if(x_same_border==0){ // 같은 라인인지 검사
                    snake.move(LEFT);
                    snake.body[0][1]=gateY2;
                  }else{
                    command=2; // right
                    snake.move(RIGHT);
                    snake.body[0][1]=0;
                  }
                }else if(snake.body[0][0]==gateX2){ // gateX2로 들어갈 때
                  snake.body[0][0]=gateX1;
                  gateCount=-10;
                  if(x_same_border==0){
                    snake.move(RIGHT);
                    snake.body[0][1]=gateY1;
                  }else{
                    command=2; // right
                    snake.move(RIGHT);
                    snake.body[0][1]=59;
                  }
                }
              }else if(snake.body[0][1]==59){ // 오른쪽 gate로 갈때

                if(snake.body[0][0]==gateX1){
                  snake.body[0][0]=gateX2;
                  snake.body[0][1]=gateY2;
                  gateCount=-10;
                  if(x_same_border==0){
                    snake.move(RIGHT);
                  }else{
                    command=3; // left
                    snake.move(LEFT);
                  }
                }else if(snake.body[0][0]==gateX2){
                  snake.body[0][0]=gateX1;
                  snake.body[0][1]=gateY1;
                  gateCount=-10;
                  if(x_same_border==0){
                    snake.move(RIGHT);
                  }else{
                    command=3; //left
                    snake.move(LEFT);
                  }
                }
              }
            break;

            case 1: // y_line, y_line
              if(snake.body[0][0]==0){ // 위쪽 gate로 갈때
                if(snake.body[0][1]==gateY1){ // gateY1로 들어갈 때
                  snake.body[0][1]=gateY2;
                  gateCount=-10;
                  if(y_same_border==0){ // 같은 라인인지 검사
                    snake.move(DOWN);
                    snake.body[0][0]=gateX2;
                  }else{
                    command=4; // down
                    snake.move(DOWN);
                    snake.body[0][0]=gateX2;
                  }
                }else if(snake.body[0][1]==gateY2){ // gateX2로 들어갈 때
                  snake.body[0][1]=gateY1;
                  gateCount=-10;
                  if(y_same_border==0){
                    snake.move(DOWN);
                    snake.body[0][0]=gateX1;
                  }else{
                    command=1; // up
                    snake.move(UP);
                    snake.body[0][0]=gateX1;
                  }
                }
              }else if(snake.body[0][1]==59){ // 아래쪽 gate로 갈때

                if(snake.body[0][1]==gateY1){
                  snake.body[0][1]=gateY2;
                  gateCount=-10;
                  if(y_same_border==0){
                  snake.move(DOWN);
                  snake.body[0][0]=gateX2;
                  }else{
                    command=1; // up
                    snake.move(UP);
                    snake.body[0][0]=gateX2;
                  }
                }else if(snake.body[0][1]==gateY2){
                  snake.body[0][1]=gateY1;
                  gateCount=-10;
                  if(y_same_border==0){
                    snake.move(DOWN);
                    snake.body[0][0]=gateX1;
                  }else{
                    command=1; //up
                    snake.move(DOWN);
                    snake.body[0][0]=gateX1;
                  }
                }
              }

          };
        }


};
