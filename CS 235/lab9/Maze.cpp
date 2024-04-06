//
// Created by Isaac Hamm on 3/18/22.
//

#include "Maze.h"
#include <iostream>
using namespace std;

void Maze::PrintCurrentOption() {
    string userInput;
    if (x == 2 && y == 0) {
        cout << "You're at the entrance — The only way out is FORWARD!" << endl;
        PrintOptions(0);
        cin >> userInput;
        while (true) {
            if (userInput == "forward" ||
               userInput == "left" ||
               userInput == "right") {
                break;
            }
            else {
                cout << "Choose a valid option coward! You can only get out by going THROUGH the maze!" << endl;
                cin >> userInput;
                continue;
            }
        }
        UpdateCoordinates(userInput);
        PrintCurrentOption();
    }
    else if (x == 2 && y == 1) {
        cout << "This one here is a BIG decision" << endl;
        PrintOptions(0);
        cin >> userInput;
        while (true) {
            if (userInput == "FORWARD") {
                userInput = "forward";
                break;
            }
            else if (userInput == "LEFT") {
                userInput = "left";
                break;
            }
            else if (userInput == "RIGHT") {
                userInput = "right";
                break;
            }
            else if (userInput == "BACK") {
                userInput = "back";
                break;
            }
            else {
                cout << "Choose a valid option! Remember to think BIG!" << endl;
                cin >> userInput;
                continue;
            }
        }
        UpdateCoordinates(userInput);
        PrintCurrentOption();


    }
};

void Maze::UpdateCoordinates(string& userInput) {
    if (userInput == "forward") {
        y += 1;
    }
    else if (userInput == "right") {
        x += 1;
    }
    else if (userInput == "left") {
        x -= 1;
    }
    else if (userInput == "back") {
        y -= 1;
    }
};

void Maze::PrintOptions(int option) {
    cout << "Your current position is: " << endl;
    PrintPosition();
    if (option == 0) {
        cout << "Your options are:\n"
                "[forward]\n"
                "[left]\n"
                "[right]\n"
                "[back]\n"
             << endl;
    }
};

void Maze::PrintPosition() {
    for (int i = 4; i >= 0; --i) {
        for (int j = 4; j >= 0; --j) {
            if (j == x && i == y) {
                cout << " 0 " ;
            }
            else {
                cout << " * ";
            }
        }
        cout << endl;
    }

};

void Maze::PrintIntersection() {
    cout <<
         "           |          |           \n"
         "           |          |           \n"
         "           |          |           \n"
         "           |          |           \n"
         "———————————            ———————————\n"
         "                                  \n"
         "                                  \n"
         "———————————            ———————————\n"
         "           |          |          \n"
         "           |          |          \n"
         "           |          |          \n"
         "           |          |          \n"
         << endl;
};

void Maze::PrintPlayer() {
    cout <<
         "                ———         \n"
         "               |   |        \n"
         "                ———         \n"
         "                 |          \n"
         "               / | \\         \n"
         "              /  |  \\        \n"
         "                / \\            \n"
         "               |   |           \n"
         << endl;
};

void Maze::PrintPlayerWithSword() {
    cout <<
         "          /|\\              /\\  \n"
         "          |||             ///\n"
         "          |||   ———      ///   \n"
         "          |||  |   |    ///   \n"
         "         —————  ———   ——————   \n"
         "           |     |      /   \n"
         "           |___/ | \\___/         \n"
         "                 |         \n"
         "                / \\            \n"
         "               |   |           \n"
         << endl;
}

void Maze::PrintSword() {
//    cout <<
//         "           /|\\            \n"
//         "           |||           \n"
//         "           |||             \n"
//         "           |||                \n"
//         "          —————            \n"
//         "            |          \n"
//         "            |                \n"
//         "                       \n"
//         << endl;
//
//    cout <<
//         "           /\\            \n"
//         "          ///           \n"
//         "         ///               \n"
//         "        ///                   \n"
//         "      ——————            \n"
//         "       /          \n"
//         "      /                    \n"
//         "                       \n"
//         << endl;
//
    cout <<
         "           /|\\                  /\\                 \n"
         "           |||                 ///               \n"
         "           |||                ///                \n"
         "           |||               ///                  \n"
         "          —————            ——————            \n"
         "            |               / \n"
         "            |              /  \n"
         "                       \n"
         << endl;
};