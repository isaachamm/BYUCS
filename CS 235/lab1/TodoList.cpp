//
// Created by Isaac Hamm on 1/16/22.
//

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include "TodoList.h"

using namespace std;

//Checked off by Cheuk Yan Chan
//TodoList::TodoList() {}       These are defined in the header already (don't need them here again)
//TodoList::~TodoList() {}

const char *const todoFile = "TODOList.txt";

TodoList::TodoList() {
    string line;
    ifstream inFile(todoFile);

    if (inFile.is_open()){
/*       while (!inFile.eof()) {
           if (dates.size() == tasks.size()) {
               getline(inFile, line);
               dates.push_back(line);
           }
           else {
               getline(inFile, line);
               tasks.push_back(line);
           }
       }
*/
        while (getline(inFile, line)){
            tasks.push_back(line);
        }
        inFile.close();
    }

 }

TodoList::~TodoList() {
    ofstream outFile(todoFile);

    if (outFile.is_open()){
        for (int i = 0; i < tasks.size(); ++i) {
          //      outFile << dates.at(i) << endl;
                outFile << tasks.at(i) << endl;
        }
    }
    outFile.close();
}

void TodoList::add(string _duedate, string _task) {


//    dates.push_back(_duedate);
    tasks.push_back(_duedate);
    tasks.push_back(_task);

    //cout << "Added " << dates.back() << " " << tasks.back() << endl;


    /*ofstream outFile(todoFile, ios_base::app);
    if (outFile.is_open()){
        outFile << _duedate << endl;
        outFile << _task << endl;
        outFile.close();
    }
    else {
        cout << "could not open todoFile" << endl;
    }


    /*
    *   Adds an item to the to do list with the data specified by the string "_duedate" and the task specified by "_task"
    */
}
void TodoList::remove(string _task) {

    //TODO this is the last thing I need to fix.

    string temp;

    for (int i = 0; i < tasks.size(); ++i){
        if (tasks.at(i) == _task){
  //          dates.erase(dates.begin() + i);
                tasks.erase(tasks.begin() + i);
            tasks.erase(tasks.begin() + i);


  //          cout << "Removed " << tasks.at(i) << " on " << dates.at(i) << endl;
        }
    }



    /*string temp;

    ifstream inFile1(todoFile);
    if (inFile1.is_open()){
        while (!inFile1.eof()) {
            getline(inFile1, temp);
            if (temp == _task){
                cout << "Removed task " << _task << " from TODOList.txt" << endl;
            }
            else {
                ofstream outFile1("tempfile.txt", ios_base::app);
                if (outFile1.is_open()) {
                    outFile1 << temp << endl;
                    outFile1.close();
                }
                else {
                    cout << "outFile did not open" << endl;
                }
            }
        }
        inFile1.close();
    } else {
        cout << "inFile did not open" << endl;
    }

    remove(todoFile);
    rename("tempfile.txt", todoFile);

    //TODO fix below to rewrite to a new file
    /*
    ifstream inFile2(temp);
    ofstream outFile2(todoFile, ios_base::app);
    if (outFile2.is_open() && inFile2.is_open()){
        getline(inFile2, temp);
        outFile2 << temp << endl;
        outFile2.close();
    }
    else {
        cout << "could not open outFile" << endl;
    }
    */

    /*
    *   Removes an item from the to do list with the specified task name
    *
    *   Returns 1 if it removes an item, 0 otherwise
    */
}
void TodoList::printTodoList() {


    for (int i = 0; i < tasks.size(); ++i){
  //      cout << dates.at(i) << endl;
        cout << tasks.at(i) << endl;
    }

    /*string temp;

    ifstream inFile(todoFile);
        if (inFile.is_open()){
            while (!inFile.eof()) {
                getline(inFile, temp);
                cout << temp << endl;
            }
        } else {
            cout << "file did not open" << endl;
        }



    /*
    *   Prints out the full to do list to the console
    */

}
void TodoList::printDaysTasks(string _date) {

    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks.at(i) == _date) {
            cout << tasks.at(i) << endl;
            cout << tasks.at(i + 1) << endl;
        }
    }

    /*string temp;

    ifstream inFile(todoFile);
    if (inFile.is_open()){
        while (!inFile.eof()) {
            getline(inFile, temp);
            if (temp == _date) {
                getline(inFile, temp);
                cout << temp << endl;
            }
        }
    } else {
        cout << "file did not open" << endl;
    }


    /*
    *   Prints out all items of a to do list with a particular due date (specified by _duedate)
    */
}