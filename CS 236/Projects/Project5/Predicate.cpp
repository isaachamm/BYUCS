//
// Created by Isaac Hamm on 7/6/22.
//

#include "Predicate.h"
#include <sstream>

void Predicate::addParameter(Parameter parameter) {
    parameters.push_back(parameter);
}

void Predicate::addParameter(string parameterValue) {
    Parameter parameter;
    parameter.setValue(parameterValue);
    parameters.push_back(parameter);
}
string Predicate::toString() const {
    string sep = "";
    stringstream sstream;
    sstream << name << "(";
    for (Parameter currParam : parameters) {
        sstream << sep << currParam.toString();
        sep = ",";
    }
    sstream << ")";
    return sstream.str();
}