#include "GateController.h"




void Gate::syncMap(){
  for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      if(gateMap.m[i][j]==1){
        gateList.push_back(pair<int,int>(i,j));
      }
    }
  }

}


void Gate::gateRefresh(){
  int gateChoice1,gateChoice2;


  gateChoice1=rand()%(gateList.size());
  gateChoice2=rand()%(gateList.size());

  // gateChoice1=81;
  // gateChoice2=100;
  while (gateChoice1==gateChoice2){
      gateChoice2=rand()%(gateList.size());
  }



  gate1=make_pair(gateList[gateChoice1].first,gateList[gateChoice1].second);
  gate2=make_pair(gateList[gateChoice2].first,gateList[gateChoice2].second);


  gateMap.m[gate1.first][gate1.second]=GATE_COUNT;
  gateMap.m[gate2.first][gate2.second]=GATE_COUNT;
}

void Gate::gateSensor(){
  if(snake.body[0][0]==gate1.first && snake.body[0][1]==gate1.second){
    usedGateCount++;
    if(gate2.first==0){
      command=4; //down
    }else if (gate2.first==29){
      command= 1;// up
    }else if(gate2.second==0){
      command=2; // right
    }else if(gate2.second==59){
      command= 3;//left
    }else{
        if(gate1.first!= gate2.first && gate1.second!=gate2.second){
          if(command==3){
            command=1;
          }else if(command==2){
              command=4;
          }else if(command==1){
            command=2;
          }else if(command==4){
            command=3;
          }
        }
    }
    snake.body[0][0]=gate2.first;
    snake.body[0][1]=gate2.second;
    string state4 = "G:"+to_string(usedGateCount);

    mvwprintw(board.score_board, 8, 5, state4.c_str());

    if(usedGateCount>=goal_gateCount){
      mvwprintw(board.mission_board, 8, 5, mission_gateCount.c_str());
    }

  }else if(snake.body[0][0]==gate2.first && snake.body[0][1]==gate2.second){
    usedGateCount++;
    if(gate1.first==0){
      command=4; //down
    }else if (gate1.first==29){
      command= 1;// up
    }else if(gate1.second==0){
      command=2; // right
    }else if(gate1.second==59){
      command= 3;//left
    }else{
      if(gate1.first!= gate2.first && gate1.second!=gate2.second){
        if(command==3){
          command=1;
        }else if(command==2){
            command=4;
        }else if(command==1){
          command=2;
        }else if(command==4){
          command=3;
        }
      }
    }
    snake.body[0][0]=gate1.first;
    snake.body[0][1]=gate1.second;

    string state4 = "G:"+to_string(usedGateCount);
    mvwprintw(board.score_board, 8, 5, state4.c_str());
    if(usedGateCount>=goal_gateCount){
      mvwprintw(board.mission_board, 8, 5, mission_gateCount.c_str());
    }

  }

}
