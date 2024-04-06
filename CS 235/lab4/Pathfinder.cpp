//
// Created by Isaac Hamm on 2/4/22.
//

#include "Pathfinder.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "stdlib.h"

using namespace std;

Pathfinder::Pathfinder() {
    initialize_random_seed();

    for (int i = 0; i < MAZE_SIZE; ++i) {   //This is to generate a maze of all 1s if no maze is imported
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                maze[k][j][i] = 1;
            }
        }
    }
}

string Pathfinder::toString() const {
    stringstream generator; //stringstream that will take the input in to create the maze.
    vector<int> x;          //these vectors represent the coordinates
    vector<int> y;
    vector<int> z;
    int mazeGen[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
    string space = " ";
    string newLine = "\n";
    string map;


    if (maze [0][0][0] == 1) {
        for (int i = 0; i < MAZE_SIZE; ++i) {           //These loops are to turn the maze into a string
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    generator << maze[k][j][i] << space;
                }
                generator << newLine;
            }
            if (i < MAZE_SIZE - 1) {
                generator << newLine;
            }
        }
        map = generator.str();
    }
    else {
        for (int i = 0; i < MAZE_SIZE; ++i) {   //This is to generate a maze of all 1s if no maze is imported
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    mazeGen[k][j][i] = 1;
                }
            }
        }

        for (int i = 0; i < MAZE_SIZE; ++i) {           //These loops are to turn the maze into a string
            for (int j = 0; j < MAZE_SIZE; ++j) {
                for (int k = 0; k < MAZE_SIZE; ++k) {
                    generator << mazeGen[k][j][i] << space;
                }
                generator << newLine;
            }
            if (i < MAZE_SIZE - 1) {
                generator << newLine;
            }
        }
        map = generator.str();
    }

    return map;
}

void Pathfinder::createRandomMaze() {

    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                maze[k][j][i] = rand() % 2;
            }
        }
    }
    maze[0][0][0] = 1;
    maze[MAZE_SIZE - 1][MAZE_SIZE - 1][MAZE_SIZE -1] = 1;

    solveMaze();

}

bool Pathfinder::importMaze(string file_name) {

    solution.clear();
    stringstream stringToNumber;
    string line;
    int counter = 0;

    ifstream ifs(file_name);
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            getline(ifs, line);
            stringToNumber << line << endl;
            counter ++;
        }
        ifs.close();
    }
    if (counter != 29) {         //checks the size of the maze
        return false;
    }


    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                stringToNumber >> maze[k][j][i];    //this SHOULD parse each number into the maze array.
                if (maze[k][j][i] == 0 || maze[k][j][i] == 1) {   //this is to make sure that the maze is valid based on number of things
                    continue;
                } else {
                    return false;
                }
            }
        }
    }
    if (maze[0][0][0] == 1 &&
        maze[MAZE_SIZE - 1][MAZE_SIZE - 1][MAZE_SIZE - 1] == 1) {  //checks that the maze starts and ends with 1
        return true;
    } else {
        return false;
    }
}


vector<string> Pathfinder::solveMaze() {
    solution.clear();
    int mazeCopy[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];

    for (int i = 0; i < MAZE_SIZE; ++i) {
        for (int j = 0; j < MAZE_SIZE; ++j) {
            for (int k = 0; k < MAZE_SIZE; ++k) {
                mazeCopy[k][j][i] = maze[k][j][i];
                }
            }
        }

    if (FindMazePath(mazeCopy, 0, 0, 0)) {
        reverse(solution.begin(), solution.end());
        return solution;
    }
    else {
        solution.clear();
        return solution;
    }
}

bool Pathfinder::FindMazePath(int maze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE], int x, int y, int z) {

    if (x > (MAZE_SIZE - 1) || y > (MAZE_SIZE - 1) ||      // Out of bounds
        z > (MAZE_SIZE - 1) || x < 0 || y < 0 || z < 0) {
        return false;
    }
    else if (maze [x][y][z] != 1) {                         // Wrong path (0s)
        return false;
    }
    else if (x == (MAZE_SIZE - 1) && y == (MAZE_SIZE - 1) && z == (MAZE_SIZE - 1)) {    //Base case - at 4,4,4
        maze [x][y][z] = EXPLORED;
        stringstream solutionString;
        solutionString << "(" << x << ", " << y << ", " << z << ")";
        solution.push_back(solutionString.str());
        return true;
    }
    else {
        maze [x][y][z] = EXPLORED;

        if (FindMazePath(maze, (x + 1), y, z) ||
            FindMazePath(maze, (x - 1), y, z) ||
            FindMazePath(maze, x, (y + 1), z) ||
            FindMazePath(maze, x, (y - 1), z) ||
            FindMazePath(maze, x, y, (z + 1)) ||
            FindMazePath(maze, x, y, (z - 1))) {
            stringstream solutionString;
            solutionString << "(" << x << ", " << y << ", " << z << ")";
            solution.push_back(solutionString.str());
            return true;
        }
        else {
            maze[x][y][z] = DEAD_END;
        }
        return false;
    }

}
