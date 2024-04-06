//
// Created by Isaac Hamm on 7/6/22.
//

#ifndef LAB2_PARAMETER_H
#define LAB2_PARAMETER_H

#include<string>

using namespace std;

class Parameter {

private:
    string value;

public:
    Parameter() {};
    ~Parameter() {};

    const string &getValue() const { return value; }
    void setValue(const string &newValue) { value = newValue; }
    string toString() { return value; }
    bool isConst() const {
        if(value.at(0) == '\'') {
            return true;
        }
        else return false;
    }

};


#endif //LAB2_PARAMETER_H