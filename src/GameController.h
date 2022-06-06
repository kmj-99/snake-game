#include <ncurses.h>
#include "Map.h"
#include "Snake.h"
#include "BoardController.h"
#include "GateController.h"
#include "Item.h"
#include <signal.h>

#define UP 259
#define RIGHT 261
#define LEFT 260
#define DOWN 258

bool _signal = true;

// when receive alarm, set _siganl true
void sig_alrm(int signum){
  _signal = false;
}

//
class GameController{
    public:
        friend class Item;
        vector<Item> itemContainer;
        Map map;
        Snake snake;
        BoardController board;
        Gate gate;
        int keyIn, command = 2, gateCount = 0, itemCount = 0;
        //Constructor
        GameController() : board(), snake(), gate(map, snake, command, gateCount) {
            //alarm handler
            signal(SIGALRM, sig_alrm);
            //Gate controller
            game_start();
        }

    void game_start(){
            gate.gateRefresh(); // gateRefresh
            while(true){
                
                //gate controller
                if(gateCount == 10){
                  gateCount = -50;
                  gate.gateRefresh();
                }
                
                //item controller
                if(itemCount == 15){
                  bool randomItem = rand() % 2 ? true : false;
                  Item item((1 + rand()) % 28, (1 + rand()) % 58, randomItem);
                  set_item(item);
                  check_item(itemContainer);
                  itemContainer.push_back(item);
                  itemCount = 0;
                }
                gateCount++;
                itemCount++;

                _signal = true;
                ualarm(100000, 0); // set alarm timer to 1sec
                while(_signal){ // receive keyboard input until alarm ringing
                    keyIn = keyboard_input();
                    command = keyIn != 0 ? keyIn : command; // if no keyboard input received, do prev action
                }
                snake.move(command);

                //snake head hit body
                if (map.m[snake.body[0][0]][snake.body[0][1]] == 3)
                    break;
                
                // if snake eat item
                if (map.m[snake.body[0][0]][snake.body[0][1]] == 4 || map.m[snake.body[0][0]][snake.body[0][1]] == 5)
                {
                    if (map.m[snake.body[0][0]][snake.body[0][1]] == 4)
                        snake.size_up();
                    else
                        snake.size_down();

                    map.m[snake.body[0][0]][snake.body[0][1]] = 0;
                    string state1 = "snake size is : " + to_string(snake.body.size());
                    mvwprintw(board.score_board, 5, 5, state1.c_str());
                }
                gate.gateSensor();
                render_map();
            }
    }


    //refresh map array every 1sec to rendering map
    void render_map(){
        clear_map();
        set_snake();
        wrefresh(board.main_board);
        wrefresh(board.score_board);
        wrefresh(board.mission_board);
        for (size_t i = 0; i < 30; i++){
            for (size_t j = 0; j < 60; j++)
            {
                if (map.m[i][j] == 0) // empty space
                {
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, " ");
                    wattroff(board.main_board, COLOR_PAIR(2));
                }
                else if(map.m[i][j] == 1){ // wall
                    wattron(board.main_board, COLOR_PAIR(1));
                    mvwprintw(board.main_board, i, j, " ");
                    wattroff(board.main_board, COLOR_PAIR(1));
                }
                else if(map.m[i][j] == 3){ // snake body
                    wattron(board.main_board, COLOR_PAIR(4));
                    mvwprintw(board.main_board, i, j, "O");
                    wattroff(board.main_board, COLOR_PAIR(4));
                }
                else if(map.m[i][j] == 10){ // Gate
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "1");
                    wattroff(board.main_board, COLOR_PAIR(2));
                }
                else if(map.m[i][j] == 2){ // snake head
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "M");
                    wattroff(board.main_board, COLOR_PAIR(2));
                }
                else if(map.m[i][j] == 4){ // Gitem
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "G");
                    wattroff(board.main_board, COLOR_PAIR(2));
                }
                else if(map.m[i][j] == 5){ // Pitem
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "P");
                    wattroff(board.main_board, COLOR_PAIR(2));
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
        for (size_t i = 0; i < 30; i++)
            for (size_t j = 0; j < 60; j++){
                if (map.m[i][j] == 3){
                  if(j==0 || j==59|| i==0 || i==29){
                    map.m[i][j]=1;
                  }else{
                    map.m[i][j] = 0;

                  }

                }
                if(gateCount==10 && map.m[i][j]==10){
                    map.m[i][j]=1;

                }
              }
    }

    //set snake in the map array
    void set_snake(){
        int tmp_x = snake.body[0][0];
        int tmp_y = snake.body[0][1];
        map.m[tmp_x][tmp_y] = 2;

        for (vector<vector<int> >::iterator i = snake.body.begin() + 1; i != snake.body.end(); i++)
        {
            tmp_x = (*i)[0];
            tmp_y = (*i)[1];
            map.m[tmp_x][tmp_y] = 3;
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
        map.m[item.x][item.y] = item.itemType ? 4 : 5;
    }

    void erase_item(Item item){
        map.m[item.x][item.y] = 0;
    }

    void check_item(vector<Item> &v){
        for (vector<Item>::iterator it = v.begin(); it != v.end(); it++)
        {
            it -> lifeTime++;
        }
        
        for (vector<Item>::iterator it = v.begin(); it != v.end(); it++)
        {
            if (it -> lifeTime == 7)
            {
                erase_item(*it);
                v.erase(it);
            }
        }
        
    }
};
