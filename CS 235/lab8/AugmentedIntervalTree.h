//
// Created by Isaac Hamm on 3/11/22.
//

#ifndef LAB8_AUGMENTEDINTERVALTREE_H
#define LAB8_AUGMENTEDINTERVALTREE_H

#include "IntervalTree.h"

using namespace std;

template <typename T>
class AugmentedIntervalTree : public IntervalTree<T>{

private:
    void _clear(Node<T>*& node) {
        if (node == nullptr) {
            return;
        }
        _clear(node->left);
        _clear(node->right);
        delete node;
    };



public:
    AugmentedIntervalTree() {
//        cout << "constructor" << endl;
    };
    ~AugmentedIntervalTree() {
        clear();
//        cout << "destructor" << endl;
    };
    void clear() override {
        _clear(this->root);
        this->root = nullptr;
//        cout << "clear function" << endl;
    };

    bool is_empty() const override {
//        cout << "isempty Function" << endl;
//        if (this->root == nullptr) {
//            return true;
//        }
//        else {
//            return false;
//        }
        return this->root == nullptr;
    };
    bool add(T const& lower, T const& upper) override {
//        cout << "add function" << endl;
        return AddInterval(this->root, lower, upper);
        //I think this one is done
    };

    vector<Interval<T>> query(T const& point) const override {
//        cout << "query function" << endl;
        vector<Interval<T>> newints;
        _query(this->root, point, newints);
        return newints;
    };

    void _query(Node<T>*const& node, T const& item, vector<Interval<T>>& items_found) const {
        if (node == nullptr) { return; }

        _query(node->left, item, items_found);
        if (item >= node->interval.lower && item < node->interval.upper) {
            items_found.push_back(node->interval);
        }
        _query(node->right, item, items_found);

    };

    bool remove(T const& lower, T const& upper) override {
//        cout << "remove function" << endl;
        bool test = RemoveInterval(this->root, lower, upper);
        return test;
    };

    bool AddInterval(Node<T>*& node, T const& lower, T const& upper) {
        bool check;
        if (node == nullptr) {
            Interval<T> newNodeInterval(lower, upper);
            node = new Node<T>(newNodeInterval);

            node->min_max = node->interval;
            return true;
        }

        if (node->interval.lower == lower) {
            if (node->interval.upper == upper) {
                return false;
            }
            else if (node->interval.upper > upper){
                check = AddInterval(node->left, lower, upper);
            }
            else if (node->interval.upper < upper) {
                check = AddInterval(node->right, lower, upper);
            }
        }
        else if (node->interval.lower < lower) {
            check = AddInterval(node->right, lower, upper);
        }
        else if (node->interval.lower > lower) {
            check = AddInterval(node->left, lower, upper);
        }

//        if (upper > node->min_max.upper) {
//            node->min_max.upper = upper;
//        }
//        if (lower < node->min_max.lower) {
//            node->min_max.lower = lower;
//        }
        _update_minmax(node);
        return check;
    };

    //TODO see if this works
//    if (node->interval.lower > node->left->min_max.lower) {
//        node->min_max.lower = node->left->min_max.lower
//    }
//    else {
//        node->min_max.lower = node->interval.lower;
//    }

    //TODO compare the node's value interval to children's min-max
    void _update_minmax (Node<T>*& node) {
        //2 null children
        if (node->left == nullptr && node->right == nullptr) {
            node->min_max.upper = node->interval.upper;
            node->min_max.lower = node->interval.lower;
        }
            //if neither child is null
        else if (node->left != nullptr && node->right != nullptr) {
            //compare the upper value to both children
            if (node->left->min_max.upper > node->right->min_max.upper) {
                if (node->interval.upper < node->left->min_max.upper) {
                    node->min_max.upper = node->left->min_max.upper;
                }
                else {
                    node->min_max.upper = node->interval.upper;
                }
            }
            else {
                if (node->interval.upper < node->right->min_max.upper) {
                    node->min_max.upper = node->right->min_max.upper;
                }
                else {
                    node->min_max.upper = node->interval.upper;
                }
            }
            //compare the lower (only need to do left, right?)
            if (node->interval.lower > node->left->min_max.lower) {
                node->min_max.lower = node->left->min_max.lower;
            }
            else {
                node->min_max.lower = node->interval.lower;
            }
        }
        //if left child is null
        else if (node->left == nullptr) {
            if (node->interval.upper < node->right->min_max.upper) {
                node->min_max.upper = node->right->min_max.upper;
            }
            else {
                node->min_max.upper = node->interval.upper;
            }
            node->min_max.lower = node->interval.lower;
        }
        //if right child is null
        else /*if (node->right == nullptr)*/ {
            //check lower minmax of left child
            if (node->interval.lower > node->left->min_max.lower) {
                node->min_max.lower = node->left->min_max.lower;
            }
            else {
                node->min_max.lower = node->interval.lower;
            }
            //check upper minmax of left child
            if (node->interval.upper < node->left->min_max.upper) {
                node->min_max.upper = node->left->min_max.upper;
            }
            else {
                node->min_max.upper = node->interval.upper;
            }
        }


//        if (node->left != nullptr) {
//            if (node->right != nullptr) {
//                if (node->interval.lower > node->left->min_max.lower) {
//                    node->min_max.lower = node->left->min_max.lower;
//                }
//                if (node->interval.upper < node->left->min_max.upper) {
//                    node->min_max.lower = node->left->min_max.lower;
//                }
//                if (node->interval.upper < node->right->min_max.upper) {
//                    node->min_max.lower = node->right->min_max.lower;
//                }
//            }
//            else {
//                if (node->interval.lower > node->left->min_max.lower) {
//                    node->min_max.lower = node->left->min_max.lower;
//                }
//                if (node->interval.upper > node->interval.upper) {
//                    node->min_max.upper = node->interval.upper;
//                }
//                if (node->interval.upper < node->left->min_max.upper) {
//                    node->min_max.lower = node->left->min_max.lower;
//                }
//            }
//        }
//        else if (node->right != nullptr) {
//            if (node->interval.upper < node->right->min_max.upper) {
//                node->min_max.upper = node->right->min_max.upper;
//            }
//        }
    };

    bool RemoveInterval(Node<T>*& node, T const& lower, T const& upper) {
        bool check;
        if (node == nullptr) {
            return false;
        }
        else if (node->interval.lower == lower) {
            if (node->interval.upper == upper) {
                if (node->left == nullptr) {
                    Node<T> *toDelete = node;
                    node = node->right;
                    delete toDelete;
                    return true;
                } else if (node->right == nullptr) {
                    Node<T> *toDelete = node;
                    node = node->left;
                    delete toDelete;
                    return true;
                } else {
                    Node<T> *iop = InOrderPredecessor(node);
                    node->interval = iop->interval;
                    RemoveInterval (node->left, iop->interval.lower, iop->interval.upper);
                    return true;
                }
            }
            else if (upper < node->interval.upper) {
                check = RemoveInterval(node->left, lower,upper);
            }
            else {
                check = RemoveInterval(node->right, lower,upper);
            }
        }
        else if (lower < node->interval.lower) {
            check = RemoveInterval(node->left, lower, upper);
        }
        else {
            check = RemoveInterval(node->right, lower, upper);
        }

//        //TODO: fix this so that it doesn't check nullptrs and lead to a seg fault
//        if (node->left == nullptr) {
//
//        }
//        if (node->min_max.upper < node->left->min_max.upper) {
//            if (node->min_max.upper < node->right->min_max.upper) {
//                node->min_max.upper = node->right->min_max.upper;
//            }
//            else {
//                node->min_max.upper = node->left->min_max.upper;
//            }
//        }
//        if (node->min_max.lower < node->left->min_max.lower) {
//            if (node->min_max.lower < node->right->min_max.lower) {
//                node->min_max.lower = node->right->min_max.lower;
//            }
//            else {
//                node->min_max.lower = node->left->min_max.lower;
//            }
//        }

        _update_minmax(node);
        return check;
    };

    Node<T>* InOrderPredecessor(Node<T>*& node) {
        Node<T>* iop = node->left;
        while (iop->right != nullptr) {
            iop = iop->right;
        }
        return iop;
    };

};


#endif //LAB8_AUGMENTEDINTERVALTREE_H
