#include <ncurses.h>
#include "Map.h"
#include "Snake.h"
#include "BoardController.h"
#include "GateController.h"
#include "Item.h"
#include "util.h"
#include <signal.h>
#ifndef GAME
#define GAME
bool _signal = true;

// when receive alarm, set _siganl true
void sig_alrm(int signum){
  _signal = false;
}

int goal_snakeSize=rand()%5+5;
int goal_growthPoint=rand()%5+5;
int goal_positionPoint=rand()%3+5;
int goal_gateCount=rand()%5+5;
class GameController{
    public:
        friend class Item;
        vector<Item> itemContainer;
        Map map;
        Snake snake;
        BoardController board;
        Gate gate;
        int keyIn, command = 2, gateCount = 0, itemCount = 0;
        pair<int,int> gate1=make_pair(0,0);
        pair<int,int> gate2=make_pair(0,0);
        int GrowthItemsCount=0 , PositionItemCount=0 , usedGateCount=0;
        string score_snakeSize = "B:" + to_string(snake.body.size());
        string score_growthPoint = "+:"+to_string(GrowthItemsCount);
        string score_positionPoint= "-:"+to_string(PositionItemCount);
        string score_gateCount = "G:"+to_string(usedGateCount);
        string mission_snakeSize = "B:" + to_string(goal_snakeSize)+" ()";
        string mission_growthPoint = "+:"+to_string(goal_growthPoint)+" ()";
        string mission_positionPoint= "-:"+to_string(goal_positionPoint)+" ()";
        string mission_gateCount = "G:"+to_string(goal_gateCount)+" ()";
        //Constructor
        GameController() : board(), snake(), gate(map, snake, command,usedGateCount,board,gate1,gate2,goal_gateCount) {
            //alarm handler
            signal(SIGALRM, sig_alrm);
            //Gate controller
            game_run();
        }


        void game_run(){

            mvwprintw(board.score_board, 5, 5, score_snakeSize.c_str());
            mvwprintw(board.score_board, 6, 5, score_growthPoint.c_str());
            mvwprintw(board.score_board, 7, 5, score_positionPoint.c_str());
            mvwprintw(board.score_board, 8, 5, score_gateCount.c_str());


            mvwprintw(board.mission_board, 5, 5, mission_snakeSize.c_str());
            mvwprintw(board.mission_board, 6, 5, mission_growthPoint.c_str());
            mvwprintw(board.mission_board, 7, 5, mission_positionPoint.c_str());
            mvwprintw(board.mission_board, 8, 5, mission_gateCount.c_str());

            for(int i=0;i<HEIGHT;i++){
              for(int j=0;j<WIDTH;j++){
                map.m[i][j]=map.m4[i][j];
              }
            }
            gate.syncMap();
            gate.gateRefresh(); // gateRefresh
            while(true){
                //gate controller
                if(gateCount == GATE_COUNT){
                  gateCount = -50;
                  gate.gateRefresh();
                }

                //item controller
                item_setter();

                _signal = true;
                ualarm(100000, 0); // set alarm timer to 1sec
                while(_signal){ // receive keyboard input until alarm ringing
                    keyIn = keyboard_input();
                    command = keyIn != 0 ? keyIn : command; // if no keyboard input received, do prev action
                }
                snake.move(command);

                //snake head hit body
                if (map.m[snake.body[0][0]][snake.body[0][1]] == SNAKE_BODY)
                    break;

                //snake head wall
                if (map.m[snake.body[0][0]][snake.body[0][1]] == WALL)
                    break;

                // if snake eat item
                check_snake_eat();

                gate.gateSensor();

                if (snake.body.size() < 3 || snake.body.size() > 10)
                {
                    break;
                }

                render_map();
            }
            while (true)
            {
                /* code */
            }

    }

    void check_snake_eat(){



      if (map.m[snake.body[0][0]][snake.body[0][1]] == GITEM || map.m[snake.body[0][0]][snake.body[0][1]] == PITEM)
          {
              if (map.m[snake.body[0][0]][snake.body[0][1]] == GITEM){
                  snake.size_up();
                  GrowthItemsCount++;
                }else{
                  snake.size_down();
                PositionItemCount++;
                }
              map.m[snake.body[0][0]][snake.body[0][1]] = EMPTY_SPACE;
              score_snakeSize = "B:" + to_string(snake.body.size());
              score_growthPoint = "+:"+to_string(GrowthItemsCount);
              score_positionPoint="-:"+to_string(PositionItemCount);

              mvwprintw(board.score_board, 5, 5, score_snakeSize.c_str());
              mvwprintw(board.score_board, 6, 5, score_growthPoint.c_str());
              mvwprintw(board.score_board, 7, 5, score_positionPoint.c_str());

          }

        if(snake.body.size()==goal_snakeSize){
            mission_snakeSize = "B:" + to_string(goal_snakeSize)+" (V)";
            mvwprintw(board.mission_board, 5, 5, mission_snakeSize.c_str());
        }

        if(GrowthItemsCount==goal_growthPoint){
          mission_growthPoint = "+:"+to_string(goal_growthPoint)+" (V)";
          mvwprintw(board.mission_board, 6, 5, mission_growthPoint.c_str());


        }

        if(PositionItemCount==goal_positionPoint){
          mission_positionPoint= "-:"+to_string(goal_positionPoint)+" (V)";
          mvwprintw(board.mission_board, 7, 5, mission_positionPoint.c_str());

        }



    }

    void item_setter(){
        if(itemCount == ITEM_COUNT){
            bool randomItem = rand() % 2 ? true : false;
                int rand_x = rand() % HEIGHT;
                int rand_y = rand() % WIDTH;

                while(!is_empty(rand_x, rand_y)){
                rand_x = rand() % HEIGHT;
                rand_y = rand() % WIDTH;
                }
                Item item(rand_x, rand_y, randomItem);
                set_item(item);
                check_item(itemContainer);
                itemContainer.push_back(item);
                itemCount = 0;
            }
            gateCount++;
            itemCount++;
    }

    //refresh map array every 1sec to rendering map
    void render_map(){
        clear_map();
        set_snake();
        wrefresh(board.main_board);
        wrefresh(board.score_board);
        wrefresh(board.mission_board);
        for (size_t i = 0; i < HEIGHT; i++){
            for (size_t j = 0; j < WIDTH; j++)
            {
                switch (map.m[i][j])
                {
                case EMPTY_SPACE:
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, " ");
                    wattroff(board.main_board, COLOR_PAIR(2));
                    break;
                case WALL:
                    wattron(board.main_board, COLOR_PAIR(1));
                    mvwprintw(board.main_board, i, j, " ");
                    wattroff(board.main_board, COLOR_PAIR(1));
                    break;
                case IMMUNE_WALL:
                    wattron(board.main_board, COLOR_PAIR(1));
                    mvwprintw(board.main_board, i, j, " ");
                    wattroff(board.main_board, COLOR_PAIR(1));
                    break;
                case SNAKE_BODY:
                    wattron(board.main_board, COLOR_PAIR(4));
                    mvwprintw(board.main_board, i, j, "O");
                    wattroff(board.main_board, COLOR_PAIR(4));
                    break;
                case SNAKE_HEAD:
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "M");
                    wattroff(board.main_board, COLOR_PAIR(2));
                    break;
                case GATE:
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "1");
                    wattroff(board.main_board, COLOR_PAIR(2));
                    break;
                case GITEM:
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "G");
                    wattroff(board.main_board, COLOR_PAIR(2));
                    break;
                case PITEM:
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "P");
                    wattroff(board.main_board, COLOR_PAIR(2));
                    break;
                }
            }

        refresh();
        wrefresh(board.main_board);
        wrefresh(board.score_board);
        wrefresh(board.mission_board);
    };
}
    //erase snake before rendering snake inside map
    void clear_map(){


        for (size_t i = 0; i < HEIGHT; i++)
            for (size_t j = 0; j < WIDTH; j++){
                if (map.m[i][j] == SNAKE_BODY){
                  if(j == 0 || j == (WIDTH - 1)|| i == 0 || i == (HEIGHT - 1) || (i==gate1.first && j==gate1.second) || (i==gate2.first && j==gate2.second)){
                    map.m[i][j] = WALL;
                  }else{
                    map.m[i][j] = EMPTY_SPACE;
                  }
                }
                if(gateCount == 10 && map.m[i][j] == GATE){
                    map.m[i][j] = WALL;
                }
              }
    }

    //set snake in the map array
    void set_snake(){
        int tmp_x = snake.body[0][0];
        int tmp_y = snake.body[0][1];
        map.m[tmp_x][tmp_y] = SNAKE_HEAD;

        for (vector<vector<int> >::iterator i = snake.body.begin() + 1; i != snake.body.end(); i++)
        {
            tmp_x = (*i)[0];
            tmp_y = (*i)[1];
            map.m[tmp_x][tmp_y] = SNAKE_BODY;
        }
    }

    // return keyboard input
    int keyboard_input(){
        int input = getch();
        switch(input)
        {
            case UP:
                return 1;
            case RIGHT:
                return 2;
            case LEFT:
                return 3;
            case DOWN:
                return 4;
            case KEY_BACKSPACE:
                return 5;
        }
        return 0;
    }

    void set_item(Item item){
        map.m[item.x][item.y] = item.itemType ? GITEM : PITEM;
    }

    void expired_item(Item item){
        map.m[item.x][item.y] = EMPTY_SPACE;
    }

    void check_item(vector<Item> &v){
        for (vector<Item>::iterator it = v.begin(); it != v.end(); it++)
        {
            it -> lifeTime++;
        }

        for (vector<Item>::iterator it = v.begin(); it != v.end(); it++)
        {
            if (it -> lifeTime == ITEM_LIFE_TIME)
            {
                expired_item(*it);
                v.erase(it);
            }
        }

    }

    bool is_empty(int x, int y){
        return map.m[x][y] == EMPTY_SPACE;
    }
};
#endif
