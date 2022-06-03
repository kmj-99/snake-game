#include <ncurses.h>
#include "Map.h"
#include "Snake.h"
#include "BoardController.h"
#include "GateController.h"
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
        Map map;
        Snake snake;
        BoardController board;
        int gateCount = 0;
        int gateX1=0,gateY1=0 , gateX2=0 , gateY2=0 , gateShape=0;
        int gateXBorder=0,gateYBorder=0;
        //Constructor
        GameController() : board(), snake() {

            //alarm handler
            signal(SIGALRM, sig_alrm);

            //rendering map by 1sec with keyboard input
            render_map();

            int tmp, command;
            Gate gate(map,snake,command,gateCount);

            gate.gateRefresh(); // gateRefresh


            while(true){
                if(gateCount == 10){
                  gateCount=-50;
                  gate.gateRefresh();

                }
                gateCount++;
                _signal = true;
                ualarm(100000, 0); // set alarm timer to 1sec
                while(_signal){ // receive keyboard input until alarm ringing
                    tmp = keyboard_input();
                    command = tmp != 0 ? tmp : command; // if no keyboard input received, do prev action
                }
                snake.move(command);


                gate.gateSensor();



                string state1 = to_string(snake.body[0][0]);
                string state2 = "x: " + state1 + " y: " + to_string(snake.body[0][1]);
                mvwprintw(board.score_board, 5, 5, state2.c_str());
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
                else if(map.m[i][j] == 4){ // item
                    wattron(board.main_board, COLOR_PAIR(2));
                    mvwprintw(board.main_board, i, j, "I");
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
};
