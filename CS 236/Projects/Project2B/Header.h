//
// Created by Isaac Hamm on 7/11/22.
//

#ifndef LAB2_HEADER_H
#define LAB2_HEADER_H

#include "Tuple.h"
#include <string>
#include <vector>

using namespace std;

class Header {

private:
    vector<string> attributes;

public:
    Header() { }
    Header(vector<string> attributes) : attributes(attributes) { }

    unsigned int size() {
        return attributes.size();
    }

    string& at(unsigned int index) {
        return attributes.at(index);
    }

    void push_back(string value) {
        attributes.push_back(value);
    }
};


#endif //LAB2_HEADER_H