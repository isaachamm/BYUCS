//started 3/19/22 @ 16:02 – 17:05

#include <iostream>
#include "Maze.h"


int main() {
    Maze newMaze;

    cout << "Welcome to the maze!\n"
            "There are exactly (9) rules you need to follow to get through the maze\n"
            "1) Don't get hit by arrows\n"
            "2) You'll never have to walk in a CURVY line\n"
            "3) ALWAYS type in lowercase\n"
            "4) Use your big sword\n"
            "5) Don't try and escape — the god of the maze doesn't like that\n"
            "6) Valgrind is the god of the maze\n"
            "7) You can't walk through walls\n"
            "8) You can only escape the maze by getting through it\n"
            "9) Don't get hit by arrows\n"
            "10) Only trust the rules 90% of the time\n"
            "\n"
            "\n"
            "You are at the entrance of the maze...\n";

    newMaze.PrintIntersection();
    newMaze.PrintPlayer();

    cout << "You find a BIG SWORD!\n";

    newMaze.PrintSword();
    string user;
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


//    newMaze.PrintCurrentOption();


    return 0;
}
