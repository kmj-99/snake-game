#include <vector>

using namespace std;

class Snake{
    public:
        //snake vector ((head x, head y),(body x, body y),(body)(body)...)
        vector<vector<int> > body; // body just follow head
        int size; // size of snake, default = 1

        //Constructor
        Snake(int size = 1) : size(size){
            vector<int> head{15, 30};
            body.push_back(head);
        };

        //size up
        void size_up(){};

        //move snake
        void move(int command){
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
    }
};
