//
// Created by Isaac Hamm on 3/1/22.
//

#ifndef LAB7_BST_H
#define LAB7_BST_H

#include "BSTInterface.h"
#include "Node.h"

class BST : public BSTInterface {

protected:
    Node* root;

public:
    BST() {root = nullptr;};
    ~BST() {clear();};

    Node* getRootNode() const;
    bool add(int data);
    bool remove(int data);
    void clear();
};


#endif //LAB7_BST_H
