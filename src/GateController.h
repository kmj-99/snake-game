#include "Map.h"
#include <cstdlib>
#include <ctime>

using namespace std;


class Gate{
    public:
        Map& gateMap;
        Gate(Map& map) : gateMap(map){};
        int x=-1,y=-1;
        int x2=-1, y2=-1;
        int resX1=-1,resY1=-1;
        int resX2=-1,resY2=-1;
        int x_border=-1 , y_border=-1;
        int x_border_left=-1, x_border_right=-1;
        int y_border_up=-1 , y_border_down=-1;
        int x_same_border=0,y_same_border=0;
        int shape=0;

        void gateRefresh(){
          x_border=-1;
          y_border=-1;
          shape=0;
          x=-1; y=-1; resX1=-1; resX2=-1; resY1=-1; resY2=-1;
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
                  resX1=x; resY1=0;
                  resX2=x2; resY2=0;
                }else{
                  gateMap.m[x][59] = 10;
                  gateMap.m[x2][59] = 10;
                  resX1=x; resY1=59;
                  resX2=x2; resY2=59;
                }

              }else{
                x_same_border=0;
                x=rand()%28 + 1;
                x2=rand()%28 + 1;
                gateMap.m[x][0]=10;
                gateMap.m[x2][59]=10;
                resX1=x; resY1=0;
                resX2=x2; resY2=59;
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
                  resX1=0; resY1=y;
                  resX2=0; resY2=y2;
                }else{
                  gateMap.m[29][y]=10;
                  gateMap.m[29][y2]=10;
                  resX1=29; resY1=y;
                  resX2=29; resY2=y2;
                }

              }else{
                y_same_border=0;
                y=rand()%58 + 1;
                y2=rand()%58 + 1;
                gateMap.m[0][y]=10;
                gateMap.m[29][y2]=10;
                resX1=0; resY1=y;
                resX2=29; resY2=y2;
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
                resX1=x; resY1=0;
              }
              else if(x_border == 1) {
                gateMap.m[x][59] = 10;
                resX1=x; resY1=59;
              }

              if(y_border == 0) {
                gateMap.m[0][y] = 10;
                resX2=0; resY2=y;
              }
              else if(y_border == 1) {
                gateMap.m[29][y] = 10;
                resX2=29; resY2=y;
              }

              break;

          };


        }

        int getX1(){
          return resX1;
        }

        int getX2(){
          return resX2;
        }

        int getY1(){
          return resY1;
        }

        int getY2(){
          return resY2;
        }

        int getXSame(){
          return x_same_border;
        }
        int getYSame(){
          return y_same_border;
        }

        int getShape(){
          return shape;
        }



        int getXBorder(){
            return x_border;
        }
        int getYBorder(){
            return y_border;
        }

};
