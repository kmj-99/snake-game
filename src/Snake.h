#include <vector>

using namespace std;

class Snake{
    public:
        //snake vector ((head x, head y),(body x, body y),(body)(body)...)
        vector<vector<int> > body;
        int size; // size of snake, default = 1
        vector<int> empty_body{15, 30};

        //Constructor
        Snake(int size = 1) : size(size){
            vector<int> head{15, 30};
            vector<int> head2{15, 29};
            vector<int> head3{15, 28};
            body.push_back(head);
            body.push_back(head2);
            body.push_back(head3);
            
        };

        //size up
        void size_up(){
            body.push_back(empty_body);
        };

        //move snake
        void move(int command){
            vector<int> tmp_head = body[0];
            vector<int> tmp;
            
            //head move first
            switch(command)
            {
                
                case 1: // up
                    body[0][0]--;
                    break;
                case 2: // right
                    body[0][1]++;
                    break;
                case 3: // left
                    body[0][1]--;
                    break;
                case 4: // down
                    body[0][0]++;
                    break;
                case 5: // backspace
                    break;
            }

            //body follow head
            for (vector<vector<int> >::iterator it = body.begin() + 1; it != body.end(); it++)
            {
                tmp = *it;
                *it = tmp_head;
                tmp_head = tmp;
            }
            empty_body[0] = tmp_head[0];
            empty_body[1] = tmp_head[1];
            // cout << empty_body[0] << empty_body[1] << endl;
        }
};
