//
// Created by Isaac Hamm on 7/6/22.
//

#include "Rule.h"
#include <sstream>

void Rule::addPredicate(Predicate predicate) {
    body.push_back(predicate);
}

void Rule::addPredicate(string name, vector<Parameter> parameters) {
    Predicate newPredicate;
    newPredicate.setName(name);
    newPredicate.setParameters(parameters);
    body.push_back(newPredicate);
}

string Rule::toString() {
    string sep = "";
    stringstream sout;
    sout << head.toString() << " :- ";
    for (Predicate currPredicate : body) {
        sout << sep << currPredicate.toString();
        sep = ",";
    }
    return sout.str();
}