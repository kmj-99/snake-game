#include "Map.h"
#include <cstdlib>
#include <ctime>
#include "util.h"
#include <iostream>
#include "Snake.h"
#include "BoardController.h"

using namespace std;


class Gate{
    public:
        Map& gateMap;
        Snake& snake;
        vector<pair<int,int>> gateList;
        pair<int,int>& gate1;
        pair<int,int>& gate2;
        int& command;
        int& usedGateCount;
        BoardController& board;
        int& goal_gateCount;
        string mission_gateCount = "G:"+to_string(goal_gateCount)+" (V)";
        Gate(Map& map,Snake& snake,int& command,int& usedGateCount,BoardController& board,pair<int ,int>& gate1, pair<int,int>& gate2,int& goal_gateCount) : gateMap(map) ,snake(snake),command(command),usedGateCount(usedGateCount),board(board),gate1(gate1),gate2(gate2),goal_gateCount(goal_gateCount){};

        void syncMap();

        void gateRefresh();


        void gateSensor();


};
