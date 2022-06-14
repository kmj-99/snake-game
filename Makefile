CC=g++
TARGET = snake
OBJECT=src/GateController.o src/BoardController.o src/Main.o

all:$(TARGET)

snake: $(OBJECT)
	$(CC) -g -o snake src/Main.cpp src/GateController.cpp src/BoardController.cpp src/GameController.cpp -std=c++11 -lncurses

GateController.o : src/GateController.cpp src/GateController.h
	$(CC) -g -c src/GateController.cpp


BoardController.o : src/BoardController.cpp src/BoardController.h
	$(CC) -g -c src/BoardController.cpp



GameController.o : src/GameController.cpp src/GameController.h
	$(CC) -g -c src/GameController.cpp



clean:
	rm -rf src/*.o src/*.exe
