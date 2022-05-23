
class Map{
    public:
        int row = 30, column = 60;
        int start_point1[2] = {5, 10};
        int start_point2[2] = {5, 73};
        int start_point3[2] = {23, 73};
        Map(){
            start_color();
            
            WINDOW *main_board, *score_board, *mission_board;
            main_board = newwin(30, 60, 5, 10);
            wbkgd(main_board, COLOR_PAIR(2));
            
            for (size_t i = 0; i < 30; i++)
                for (size_t j = 0; j < 60; j++)
                {
                    if (this -> a[i][j] == 0)
                    {
                        wattron(main_board, COLOR_PAIR(1));
                        mvwprintw(main_board, i, j, " ");
                        wattroff(main_board, COLOR_PAIR(1));
                    }
                    else{
                        wattron(main_board, COLOR_PAIR(1));
                        mvwprintw(main_board, i, j, " ");
                        wattroff(main_board, COLOR_PAIR(1));
                    }
                }
                wborder(main_board, '*', '*', '*', '*', '*', '*', '*', '*');


            score_board = newwin(15, 40, 5, 73);
            wbkgd(score_board, COLOR_PAIR(2));
            wattron(score_board, COLOR_PAIR(2));
            wborder(score_board, '*', '*', '*', '*', '*', '*', '*', '*');
            mvwprintw(score_board, 0, 14, "Score Board");
            

            mission_board = newwin(12, 40, 23, 73);
            wbkgd(mission_board, COLOR_PAIR(2));
            wattron(mission_board, COLOR_PAIR(2));
            wborder(mission_board, '*', '*', '*', '*', '*', '*', '*', '*');
            mvwprintw(mission_board, 0, 14, "Mission Board");

            wrefresh(main_board);
            wrefresh(score_board);
            wrefresh(mission_board);
        };

        int a[30][60] = {
                   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
                   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 

                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 

                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }, 
                   {0, }   
        };

        
    // void draw();
};

