//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_QUERIESAUTOMATON_H
#define LAB1_QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton {

public:
    QueriesAutomaton() {
        type = TokenType::QUERIES;
    }

private:
    void s0() {
        if (match('Q')) {
            next();
            s1();
        }
        else { sError(); }
    }
    void s1() {
        if (endOfFile()) { sError(); }
        else if (match('u')) {
            next();
            s2();
        }
        else { sError(); }
    }
    void s2() {
        if (endOfFile()) { sError(); }
        else if (match('e')) {
            next();
            s3();
        }
        else { sError(); }
    }
    void s3() {
        if (endOfFile()) { sError(); }
        else if (match('r')) {
            next();
            s4();
        }
        else { sError(); }
    }
    void s4() {
        if (endOfFile()) { sError(); }
        else if (match('i')) {
            next();
            s5();
        }
        else { sError(); }
    }
    void s5() {
        if (endOfFile()) { sError(); }
        else if (match('e')) {
            next();
            s6();
        }
        else { sError(); }
    }
    void s6() {
        if (endOfFile()) { sError(); }
        else if (match('s')) {
            next();
            return;
        }
        else { sError(); }
    }

};

#endif //LAB1_QUERIESAUTOMATON_H
