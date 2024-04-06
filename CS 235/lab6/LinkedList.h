//
// Created by Isaac Hamm on 2/19/22.
//


#ifndef LAB6_LINKEDLIST_H
#define LAB6_LINKEDLIST_H
#include "LinkedListInterface.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

template<typename T>
class LinkedList /*: public LinkedListInterface*/
{
private:
    struct Node {
        T value;
        Node* next;

        Node(T value) : value(value), next(nullptr)
        {}
    };
    Node* head;
    int listSize;

public:

LinkedList() : head(nullptr), listSize(0) {};
~LinkedList(){
    clear();
};
void insertHead(T value) {
    if (listSize == 0) {
        head = new Node(value);
        listSize++;
    }
    else {
        for (Node* iterator = head; iterator != nullptr; iterator = iterator->next) {
            if (iterator->value == value) {
//                cout << "Duplicate value" << endl;
                return;
            }
        }
        Node* newNode = new Node(value);
        Node* oldHead = head;
        newNode->next = oldHead;
        head = newNode;
        listSize++;
    }
};
void insertTail(T value) {

    if (listSize == 0) {
        head = new Node(value);
        listSize++;
    }
    else {
        for (Node* iterator = head; iterator != nullptr; iterator = iterator->next) {
            if (iterator->value == value) {
//                cout << "Duplicate value" << endl;
                return;
            }
            else {
                if (iterator->next == nullptr) {
                    iterator->next = new Node(value);
                    listSize++;
                }
            }
        }

    }
};
void insertAfter(T value, T insertionNode) {
    for (Node *iterator = head; iterator != nullptr; iterator = iterator->next) {
        if (iterator->value == value) {
//            cout << "Duplicate value" << endl;
            return;
        }
    }
    for (Node *iterator = head; iterator != nullptr; iterator = iterator->next) {
            if (iterator->value == insertionNode) {
                Node *newNode = new Node(value);
                Node* tmp;
                tmp = iterator->next;
                iterator->next = newNode;
                newNode->next = tmp;
                listSize++;
            }
    }
};

void remove(T value) {
    if (head == nullptr) {

        return;
    }
    if (head->value == value) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        listSize--;
        return;
    }
    for (Node *iterator = head; iterator->next != nullptr; iterator = iterator->next) {
        if (iterator->next->value == value) {
            Node* tmp = iterator->next;
            iterator->next = tmp->next;
            delete tmp;
            listSize--;
            return;
        }
    }
};

void clear() {
    while (head != nullptr) {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
    }
    listSize = 0;
};

T at(int index) {
    int counter = 0;
    if (index >= listSize ||
        index < 0 ||
        listSize == 0) {
        throw out_of_range("out of range exception for 'at' function");
    }
    for (Node* it = head; it != nullptr; it = it->next) {
        if (counter == index) {
            return it->value;
        }
        ++counter;
    }
    throw out_of_range("out of range exception for 'at' function");
};

int size() {return listSize;};
string toString() {
    stringstream ss;
    for (Node* it = head; it != nullptr; it = it->next) {
        ss << it->value << " ";
    }
//    ss << endl;
    return ss.str();
};

};


#endif //LAB6_LINKEDLIST_H
