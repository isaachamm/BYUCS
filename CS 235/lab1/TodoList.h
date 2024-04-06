//
// Created by Isaac Hamm on 1/16/22.
//

#ifndef LAB1_TODOLIST_H
#define LAB1_TODOLIST_H

#include "TodoListInterface.h"
#include <vector>


class TodoList: public TodoListInterface {

private:
//    vector <string> dates;
    vector <string> tasks;

public:
    TodoList();

    ~TodoList();

    void add(string _duedate, string _task);

    void remove(string _task);

    void printTodoList();

    void printDaysTasks(string _date);
};



#endif //LAB1_TODOLIST_H
