#include "Map.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Gate{
    public:
        Map& gateMap;
        Gate(Map& map):gateMap(map){
          gateMap.m[0][0]=10;

        };

        void gateRefresh(){
          int x=0,y=0;
          int x_border,y_border;


          while(x==y){
            srand((unsigned int)time(NULL));
            x=rand() %28+1;

            srand((unsigned int)time(NULL));
            y=rand() % 58+1;
          }


        srand((unsigned int)time(NULL));
        x_border=rand()%2;

        srand((unsigned int)time(NULL));
        y_border=rand()%2;

        if(x_border==0) gateMap.m[x][0]=10;
        else if(x_border==1) gateMap.m[x][59]=10;

        if(y_border==0) gateMap.m[0][y]=10;
        else if(y_border==1) gateMap.m[29][y]=10;




        }

};
