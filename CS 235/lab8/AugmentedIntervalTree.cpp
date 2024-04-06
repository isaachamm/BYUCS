////
//// Created by Isaac Hamm on 3/11/22.
////
//
//#ifndef LAB8_AUGMENTEDINTERVALTREE_CPP
//#define LAB8_AUGMENTEDINTERVALTREE_CPP
//
//#include "AugmentedIntervalTree.h"
//
//using namespace std;
//
//template <typename T> bool AddInterval(Node<T>*& node, T const& lower, T const& upper);
//template <typename T> bool RemoveInterval(Node<T>*& node, T const& lower, T const& upper);
//template <typename T> Node<T>* InOrderPredecessor(Node<T>*& node);
//
//
//template <typename T> AugmentedIntervalTree<T>::AugmentedIntervalTree() {
//    cout << "constructor" << endl;
//};
//template <typename T> AugmentedIntervalTree<T>::~AugmentedIntervalTree() {
//    cout << "destructor" << endl;
//};
//template <typename T> void AugmentedIntervalTree<T>::clear() {
//    cout << "clear function" << endl;
//};
//template <typename T> bool AugmentedIntervalTree<T>::is_empty() const {
//    cout << "isempty Function" << endl;
//    if (this->root == nullptr) {
//        return true;
//    }
//    else {
//        return false;
//    }
//};
//template <typename T> bool AugmentedIntervalTree<T>::add(T const& lower, T const& upper) {
//    cout << "add function" << endl;
//    return AddInterval(this->root, lower, upper);
//    //I think this one is done
//};
//
//template <typename T> vector<Interval<T>> AugmentedIntervalTree<T>::query(T const& point) const {
//    cout << "query function" << endl;
//    vector<Interval<T>> newints;
//    return newints;
//};
//template <typename T> bool AugmentedIntervalTree<T>::remove(T const& lower, T const& upper) {
//    cout << "remove function" << endl;
//    bool test = RemoveInterval(this->root, lower, upper);
//    return test;
//};
//
//template <typename T> bool AddInterval(Node<T>*& node, T const& lower, T const& upper) {
//    bool check;
//    if (node == nullptr) {
//        Interval<T> newNodeInterval(lower, upper);
//        node = new Node<T>(newNodeInterval);
//
//        node->min_max = node->interval;
//        return true;
//    }
//    if (node->interval.lower == lower) {
//        if (node->interval.upper == upper) {
//            return false;
//        }
//        else if (node->interval.upper > upper){
//            check = AddInterval(node->left, lower, upper);
//        }
//        else if (node->interval.upper < upper) {
//            check = AddInterval(node->right, lower, upper);
//        }
//    }
//    else if (node->interval.lower < lower) {
//        check = AddInterval(node->right, lower, upper);
//    }
//    else if (node->interval.lower > lower) {
//        check = AddInterval(node->left, lower, upper);
//    }
//
//    if (upper > node->min_max.upper) {
//        node->min_max.upper = upper;
//    }
//    if (lower < node->min_max.lower) {
//        node->min_max.lower = lower;
//    }
//    return check;
//}
//
//template <typename T> bool RemoveInterval(Node<T>*& node, T const& lower, T const& upper) {
//    bool check;
//    if (node == nullptr) {
//        return false;
//    }
//    else if (node->interval.lower == lower) {
//        if (node->interval.upper == upper) {
//            if (node->left == nullptr) {
//                Node<T> *toDelete = node;
//                node = node->right;
//                delete toDelete;
//                return true;
//            } else if (node->right == nullptr) {
//                Node<T> *toDelete = node;
//                node = node->left;
//                delete toDelete;
//                return true;
//            } else {
//                Node<T> *iop = InOrderPredecessor(node);
//                node->interval = iop->interval;
//                RemoveInterval (node->left, iop->interval.lower, iop->interval.upper);
//                return true;
//            }
//        }
//        else if (upper < node->interval.upper) {
//            check = RemoveInterval(node->left, lower,upper);
//        }
//        else {
//            check = RemoveInterval(node->right, lower,upper);
//        }
//    }
//    else if (lower < node->interval.lower) {
//        check = RemoveInterval(node->left, lower, upper);
//    }
//    else {
//        check = RemoveInterval(node->right, lower, upper);
//    }
//
//    //TODO: fix this so that it doesn't check nullptrs and lead to a seg fault
//    if (node->left == nullptr) {
//
//    }
//    if (node->min_max.upper < node->left->min_max.upper) {
//        if (node->min_max.upper < node->right->min_max.upper) {
//            node->min_max.upper = node->right->min_max.upper;
//        }
//        else {
//            node->min_max.upper = node->left->min_max.upper;
//        }
//    }
//    if (node->min_max.lower < node->left->min_max.lower) {
//        if (node->min_max.lower < node->right->min_max.lower) {
//            node->min_max.lower = node->right->min_max.lower;
//        }
//        else {
//            node->min_max.lower = node->left->min_max.lower;
//        }
//    }
//    return check;
//}
//
//template <typename T> Node<T>* InOrderPredecessor(Node<T>*& node) {
//    Node<T>* iop = node->left;
//    while (iop->right != nullptr) {
//        iop = iop->right;
//    }
//    return iop;
//}
//
//
//#endif //LAB8_AUGMENTEDINTERVALTREE_CPP
