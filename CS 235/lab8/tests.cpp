//
// Created by Isaac Hamm on 3/11/22.
//
#include "AugmentedIntervalTree.h"
using namespace std;

int main() {
    cout << "it's running" << endl;
    AugmentedIntervalTree<int> thisTree;

//Tests for is empty
    test("is_empty function (tree is empty)", thisTree.is_empty(), true);

//Tests for adding
    thisTree.add(5, 6);
    thisTree.add(6,10);
    string addTest = "   [6, 10)<[6, 10)>\n[5, 6)<[5, 10)>\n";
    test("testing add function", thisTree.to_string(), addTest);
    test("add normal", thisTree.add(7, 11), true);
    test("add duplicate", thisTree.add(6,10), false);
    thisTree.add(5, 9);
    thisTree.add(4, 6);
    thisTree.add(3, 7);
    thisTree.add(2, 8);
    thisTree.add(3, 9);
    thisTree.add(0, 2);
    thisTree.add(6, 9);
    cout << thisTree.to_string() << endl;

//Test for is empty
    test("is_empty function (tree is not empty)", thisTree.is_empty(), false);

//Tests query
    vector<Interval<int>> newQuery = thisTree.query(5);
    int size = newQuery.size();
    test("Query 5", size, 6);

//Tests for Remove Function
    test("remove but it isn't there", thisTree.remove(0,5), false);
    test ("Remove, and it's there",thisTree.remove(6, 10), true);
    cout << thisTree.to_string() << endl;
    test ("Remove, and adjust min-max",thisTree.remove(7, 11), true);
    test("remove and adjust min-max", thisTree.remove(0, 2), true);
    test("remove something that's not there", thisTree.remove(0,2), false);
    cout << thisTree.to_string() << endl;

//Tests clear function
    thisTree.clear();
    test("Clear, then is empty", thisTree.is_empty(), true);



    return 0;
}