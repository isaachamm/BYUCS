//
// Created by Isaac Hamm on 3/1/22.
//

#ifndef LAB7_NODE_H
#define LAB7_NODE_H


#include "NodeInterface.h"

class Node : public NodeInterface{

public:
    int value;
    Node* left;
    Node* right;

    Node();
    ~Node() {};
//    Node(int data);
    int getData() const;
    Node* getLeftChild() const;
    Node* getRightChild() const;
};


#endif //LAB7_NODE_H
