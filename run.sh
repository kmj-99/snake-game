#!/bin/bash
//
g++ -o snake src/Main.cpp src/GateController.cpp src/BoardController.cpp src/GameController.cpp -std=c++11 -lncurses && ./snake

# EOF
