//
// Created by Isaac Hamm on 7/11/22.
//

#ifndef LAB2_TUPLE_H
#define LAB2_TUPLE_H

#include "Header.h"
#include <sstream>

class Tuple {

private:

    vector<string> values;

public:
    Tuple() { }
    Tuple(vector<string> values) : values(values) { }

    const vector<string> &getValues() const {
        return values;
    }

    void setValues(const vector<string> &values) {
        Tuple::values = values;
    }

    //You must define this to allow tuples to be put into a set
    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    unsigned int size() {
        return values.size();
    }

    string& at(unsigned int index) {
        if(index >= size()) {
            throw "Tried to access out of bounds tuple (Tuple.h)";
        }
        return values.at(index);
    }

    void push_back(string value) {
        values.push_back(value);
    }

    // This goes in your tuple class, note that tuple must include Header.h
    string toString(Header header) {
        if (size() != header.size()) {
            throw "Mismatched attribute and value sizes (in Tuple.h)";
        }

        stringstream out;
        string sep = "";
        for (unsigned i = 0; i < size(); i++) {
            string name = header.at(i);
            string value = at(i);
            out << sep << name << "=" << value;
            sep = ", ";
        }
        return out.str();
    }

};


#endif //LAB2_TUPLE_H
