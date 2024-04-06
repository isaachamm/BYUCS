//
// Created by Isaac Hamm on 7/6/22.
//

#ifndef LAB2_PREDICATE_H
#define LAB2_PREDICATE_H

#include "Parameter.h"
#include <vector>
using namespace std;

class Predicate {

private:
    vector<Parameter> parameters;
    string name;

public:
    Predicate() {};
    ~Predicate() {};

    //getters
    const vector<Parameter> &getParameters() const { return parameters; }
    const string &getName() const { return name; }

    //setters
    void setParameters(const vector<Parameter> &newParameters) { parameters = newParameters; }
    void setName(const string &newName) { name = newName; }

    //adders
    void addParameter(Parameter parameter);
    void addParameter(string parameterValue);
    string toString() const;

};


#endif //LAB2_PREDICATE_H
