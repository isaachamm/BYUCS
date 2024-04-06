//
// Created by Isaac Hamm on 7/6/22.
//

#ifndef LAB2_DATALOGPROGRAM_H
#define LAB2_DATALOGPROGRAM_H

#include <set>
#include <vector>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"

using namespace std;

class DatalogProgram {

private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;

public:
    DatalogProgram() {};
    ~DatalogProgram() {};

    const vector<Predicate> &getSchemes() const { return schemes; }
    const vector<Predicate> &getFacts() const { return facts; }
    const vector<Rule> &getRules() const { return rules; }
    const vector<Predicate> &getQueries() const { return queries; }
    const set<string> &getDomain() const { return domain; }

    void setSchemes(const vector<Predicate> &schemes) { DatalogProgram::schemes = schemes; }
    void setFacts(const vector<Predicate> &facts) { DatalogProgram::facts = facts; }
    void setRules(const vector<Rule> &rules) { DatalogProgram::rules = rules; }
    void setQueries(const vector<Predicate> &queries) { DatalogProgram::queries = queries; }
    void setDomain(const set<string> &domain) { DatalogProgram::domain = domain; }

    void addFact(Predicate newFact);
    void addScheme(Predicate newScheme);
    void addRule(Rule newRule);
    void addQuery(Predicate newQuery);
    void addDomain(string newDomain);

    string toString();

};


#endif //LAB2_DATALOGPROGRAM_H
