//
// Created by Isaac Hamm on 7/6/22.
//

#include "DatalogProgram.h"
#include "Rule.h"
#include <sstream>

void DatalogProgram::addFact(Predicate newFact) {
    facts.push_back(newFact);
}

void DatalogProgram::addScheme(Predicate newScheme) {
    schemes.push_back(newScheme);
}

void DatalogProgram::addRule(Rule newRule) {
    rules.push_back(newRule);
}

void DatalogProgram::addQuery(Predicate newQuery) {
    queries.push_back(newQuery);
}

void DatalogProgram::addDomain(string newDomain) {
    domain.insert(newDomain);
}

string DatalogProgram::toString() {
    stringstream sstream;

    sstream << "Schemes(" << schemes.size() << "):" << endl;
    for (Predicate currScheme : schemes) {
        sstream << "  " << currScheme.toString() << endl;
    }
    sstream << "Facts(" << facts.size() << "):" << endl;
    for (Predicate currFact : facts) {
        sstream << "  " << currFact.toString() << "." << endl;
    }
    sstream << "Rules(" << rules.size() << "):" << endl;
    for (Rule currRule : rules) {
        sstream <<  "  " << currRule.toString() << "." << endl;
    }
    sstream << "Queries(" << queries.size() << "):" << endl;
    for (Predicate currQuery : queries) {
        sstream << "  " << currQuery.toString() << "?" << endl;
    }
    sstream << "Domain(" << domain.size() << "):" << endl;
    for (auto currItem : domain) {
        sstream << "  " << currItem << endl;
    }

    return sstream.str();

}
