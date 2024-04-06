//
// Created by Isaac Hamm on 3/1/22.
//

#include "Node.h"

using namespace std;

Node::Node() {      //Constructor sets null pointers for its children
    value = 0;
    left = nullptr;
    right = nullptr;
}

//Node::Node(int data) {  //So we can initialize with new data instead of assigning after initializing
//    value = data;
//    left = nullptr;
//    right = nullptr;
//}

int Node::getData() const {
    return value;
};

Node *Node::getLeftChild() const {
    return left;
};

Node *Node::getRightChild() const {
    return right;
};

