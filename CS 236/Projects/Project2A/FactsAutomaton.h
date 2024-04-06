//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_FACTSAUTOMATON_H
#define LAB1_FACTSAUTOMATON_H


#include "Automaton.h"

class FactsAutomaton : public Automaton {

public:
    FactsAutomaton() {
        type = TokenType::FACTS;
    }

private:
    void s0() {
        if (match('F')) {
            next();
            s1();
        }
        else { sError(); }
    }
    void s1() {
        if (endOfFile()) { sError(); }
        else if (match('a')) {
            next();
            s2();
        }
        else { sError(); }
    }
    void s2() {
        if (endOfFile()) { sError(); }
        else if (match('c')) {
            next();
            s3();
        }
        else { sError(); }
    }
    void s3() {
        if (endOfFile()) { sError(); }
        else if (match('t')) {
            next();
            s4();
        }
        else { sError(); }
    }
    void s4() {
        if (endOfFile()) { sError(); }
        else if (match('s')) {
            next();
            return;
        }
        else { sError(); }
    }

};


#endif //LAB1_FACTSAUTOMATON_H
