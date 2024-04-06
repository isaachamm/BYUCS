//
// Created by Isaac Hamm on 3/18/22.
//

#ifndef LAB9_MAZE_H
#define LAB9_MAZE_H

#include "player.h"
#include <iostream>
#include <string>

using namespace std;

class Maze {

private:
    int mazeArray[5][5];
    int x;
    int y;

public:
    Maze() {x = 2; y = 0;};
    ~Maze() {};

    void PrintIntersection();
    void PrintPlayer();
    void PrintCurrentOption();
    void PrintOptions(int option);
    void UpdateCoordinates(string& userInput);
    void PrintSword();
    void PrintPosition();
    void PrintPlayerWithSword();


};
#endif //LAB9_MAZE_H
