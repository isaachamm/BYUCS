//
// Created by Isaac Hamm on 7/11/22.
//

#ifndef LAB2_TUPLE_H
#define LAB2_TUPLE_H


class Tuple {

private:

    vector<string> values;

public:
    Tuple() { }
    Tuple(vector<string> values) : values(values) { }

    //You must define this to allow tuples to be put into a set
    ////Do we ever have to use this?
    bool operator<(const Tuple t) const {
        return values < t.values;
    }

    unsigned int size() {
        return values.size();
    }

    string& at(unsigned int index) {
        return values.at(index);
    }

    void push_back(string value) {
        values.push_back(value);
    }


    // TODO: add more delegation functions as needed

};


#endif //LAB2_TUPLE_H
