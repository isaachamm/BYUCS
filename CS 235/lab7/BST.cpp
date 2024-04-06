//
// Created by Isaac Hamm on 3/1/22.
//

#include "BST.h"

using namespace std;

//Functions for the given functions to work:
bool Insert(int data, Node*& nodeToSearch); //the add function, but with the extra necessary parameter
bool RemoveNode(int data, Node*& nodeToSearch);
bool Search(int data, Node*& nodeToSearch); // Search function
void RemoveAll(Node* nextNode);
Node* InOrderPredecessor(Node*& node);


Node *BST::getRootNode() const {
    return root;
};

bool BST::add(int data) {
    if (root == nullptr) {
        root = new Node();
        root->value = data;
        return true;
    }
    else if (root->value == data) {
        return false;
    }
    else {
        return Insert(data, root);
    }

};

bool BST::remove(int data) {
        bool test = RemoveNode(data, root);
        return test;
};

void BST::clear() {
    RemoveAll(root);
    root = nullptr;
};


bool Search(int data, Node*& nodeToSearch) {
    if (nodeToSearch == nullptr) {
        return false;
    }
    else if (data == nodeToSearch->value) {
        return true;
    }
    else if (data > nodeToSearch->value) {
        Search(data, nodeToSearch->right);
    }
    else if (data < nodeToSearch->value) {
        Search(data, nodeToSearch->left);
    }

}

bool Insert(int data, Node*& nodeToSearch) {
    if (nodeToSearch == nullptr) {
        nodeToSearch = new Node();
        nodeToSearch->value = data;
        return true;
    }
    else if (nodeToSearch->value == data) {
        return false;
    }
    else if (data > nodeToSearch->value) {
        Insert(data, nodeToSearch->right);
    }
    else if (data < nodeToSearch->value){
        Insert(data, nodeToSearch->left);
    }

}

bool RemoveNode(int data, Node*& nodeToSearch) {

    if (nodeToSearch == nullptr) {
        return false;
    }
    else if (nodeToSearch->value == data) {
        if (nodeToSearch->left == nullptr) {
            Node* toDelete = nodeToSearch;
            nodeToSearch = nodeToSearch->right;
            delete toDelete;
            return true;
        }
        else if (nodeToSearch->right == nullptr) {
            Node* toDelete = nodeToSearch;
            nodeToSearch = nodeToSearch->left;
            delete toDelete;
            return true;
        }
        else {
            Node* iop = InOrderPredecessor(nodeToSearch);
            nodeToSearch->value = iop->value;
            RemoveNode(iop->value, nodeToSearch->left);
            return true;
        }
    }
    else if (data > nodeToSearch->value) {
        return RemoveNode(data, nodeToSearch->right);
//        return true;
    }
    else if (data < nodeToSearch->value){
        return RemoveNode(data, nodeToSearch->left);
//        return true;
    }
}

void RemoveAll(Node* nextNode) {
    if (nextNode != nullptr) {
        RemoveAll(nextNode->left);
        RemoveAll(nextNode->right);
        delete nextNode;
    }
}

Node* InOrderPredecessor(Node*& node) {
    Node* iop = node->left;
    while (iop->right != nullptr) {
        iop = iop->right;
    }
    return iop;
}
