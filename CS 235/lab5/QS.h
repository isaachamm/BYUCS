//
// Created by Isaac Hamm on 2/12/22.
//

#ifndef LAB5_QS_H
#define LAB5_QS_H

#include "QSInterface.h"
#include <vector>

class QS: public QSInterface {

private:
    vector<int> intVector;
    int vectorSize;
    int spotInVector;

public:
    QS() {};
    ~QS() {};
    void sortAll();
    void quicksort(int left, int right);
    int medianOfThree(int left, int right);
    int partition(int left, int right, int pivotIndex);
    string getArray() const;
    int getSize() const;
    bool addToArray(int value);
    bool createArray(int capacity);
    void clear();

};


#endif //LAB5_QS_H
