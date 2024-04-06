//
// Created by Isaac Hamm on 2/12/22.
//

#include "QS.h"
#include <string>
#include <sstream>

using namespace std;

void QS::sortAll() {
    if (!intVector.empty()) {
        quicksort(0, spotInVector - 1);
    }
}

void QS::quicksort(int left, int right) {
    int pivotIndex = medianOfThree(left, right);        //Sets the pivot based on the new array scope
    if (intVector.empty() ||            //runs through the checks to see if everything is good
        left < 0 ||
        right > spotInVector - 1 ||
        left >= right ||
        left > pivotIndex ||
        pivotIndex < 0 ||
        pivotIndex > right) {

    }
    else {

        int tmp;                    //switch pivot and first
        tmp = intVector.at(pivotIndex);
        intVector.at(pivotIndex) = intVector.at(left);
        intVector.at(left) = tmp;

        //Initialize trackers through vector
        int up;
        int down;
        up = left + 1;
        down = right;

                            //Runs the pointers through the vector and swaps
        do {
            while (intVector.at(up) <= intVector.at(left) && up != right) {
                ++up;
            }
            while (intVector.at(down) >= intVector.at(left) && down != left) {
                --down;
            }
            if (up < down) {
                tmp = intVector.at(up);
                intVector.at(up) = intVector.at(down);
                intVector.at(down) = tmp;
            }
        } while (down > up);

//    move pivot back
        tmp = intVector.at(down);
        intVector.at(down) = intVector.at(left);
        intVector.at(left) = tmp;

        pivotIndex = down;          //Still not sure why this has to occur... Maybe because it's the ending point?

        //RECURSION
        if (right - left > 1) {
            quicksort(left, pivotIndex);
            quicksort(pivotIndex + 1, right);
        }
    }

}

int QS::medianOfThree(int left, int right) {
    if (intVector.empty() ||            //Runs through all the checks that would return -1
        left >= right ||
        left < 0 ||
        right > spotInVector - 1) {
        return -1;
    }
    int middle = ((left +right) / 2);

//Test-Check
//    cout << left << endl;
//    cout << right << endl;
//    cout << middle << endl;

    int tmp;    //temp used for switching in bubble sort
    if (intVector.at(middle) < intVector.at(left)) {
        tmp = intVector.at(middle);
        intVector.at(middle) = intVector.at(left);
        intVector.at(left) = tmp;
    }

    if (intVector.at(middle) > intVector.at(right)) {
        tmp = intVector.at(middle);
        intVector.at(middle) = intVector.at(right);
        intVector.at(right) = tmp;
    }

    if (intVector.at(middle) < intVector.at(left)) {
        tmp = intVector.at(middle);
        intVector.at(middle) = intVector.at(left);
        intVector.at(left) = tmp;
    }

    return middle;  //This is the index
}

int QS::partition(int left, int right, int pivotIndex) {
    if (intVector.empty() ||            //runs through the checks to see if everything is good
        left < 0 ||
        right > spotInVector - 1 ||
        left >= right ||
        left > pivotIndex ||
        pivotIndex > right) {
        return -1;
    }

//    pivotIndex = medianOfThree(left, right); – don't need this here because the pivot is provided

    //move pivot to first position
    int tmp;
    tmp = intVector.at(pivotIndex);
    intVector.at(pivotIndex) = intVector.at(left);
    intVector.at(left) = tmp;

    //Initialize trackers through vector
    int up;
    int down;
    up = left + 1;
    down = right;

    do {
        while (intVector.at(up) <= intVector.at(left) && up != right){
                ++up;
        }
        while (intVector.at(down) > intVector.at(left) && down != left) {
                --down;
            }
        if (up < down) {
            tmp = intVector.at(up);
            intVector.at(up) = intVector.at(down);
            intVector.at(down) = tmp;
        }
    } while (down > up);

//    move pivot back
    tmp = intVector.at(down);
    intVector.at(down) = intVector.at(left);
    intVector.at(left) = tmp;

    return down;
}

string QS::getArray() const {
    stringstream ss;
    string vectorString;

    if (intVector.empty()) {
        return vectorString;
    }

    for (int i = 0; i < spotInVector; ++i) {
        ss << intVector.at(i);
        if (i != spotInVector - 1) {
            ss << ",";
        }
    }
//Check
//    ss << endl;

    vectorString = ss.str();
    cout << vectorString;

    return vectorString;
}
int QS::getSize() const {
    return spotInVector;
}
bool QS::addToArray(int value) {
    if (spotInVector < vectorSize) {
        intVector.at(spotInVector) = value;
        ++spotInVector;
        return true;
    }
    else {
        return false;
    }
}
bool QS::createArray(int capacity) {
    if (!intVector.empty()) {
        intVector.clear();
    }
    for (int i = 0; i < capacity; ++i) {
        intVector.push_back(0);
    }
    vectorSize = capacity;
    spotInVector = 0;
//Check
//    cout << intVector.size();

    return true;
}

void QS::clear() {
    if (!intVector.empty()) {
        intVector.clear();
    }
    spotInVector = 0;
    vectorSize = 0;

}