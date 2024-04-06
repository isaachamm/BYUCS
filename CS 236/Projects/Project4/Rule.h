//
// Created by Isaac Hamm on 7/6/22.
//

#ifndef LAB2_RULE_H
#define LAB2_RULE_H

#include "Predicate.h"

class Rule {

private:
    Predicate head;
    vector<Predicate> body;

public:
    Rule() {};
    ~Rule() {};

    const Predicate &getHead() const { return head; }
    const vector<Predicate> &getBody() const { return body; }
    void setHead(const Predicate &newHead) { Rule::head = newHead; }
    void setBody(const vector<Predicate> &newBody) { Rule::body = newBody; }

    void addPredicate(Predicate predicate);
    void addPredicate(string name, vector<Parameter> parameters);
    string toString();

};


#endif //LAB2_RULE_H
