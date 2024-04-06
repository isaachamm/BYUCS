//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_SCHEMESAUTOMATON_H
#define LAB1_SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton {

public:
    SchemesAutomaton() {
        type = TokenType::SCHEMES;
    }

private:
    void s0() {
        if (match('S')) {
            next();
            s1();
        }
        else { sError(); }
    }
    void s1() {
        if (endOfFile()) { sError(); }
        else if (match('c')) {
            next();
            s2();
        }
        else { sError(); }
    }
    void s2() {
        if (endOfFile()) { sError(); }
        else if (match('h')) {
            next();
            s3();
        }
        else { sError(); }
    }
    void s3() {
        if (endOfFile()) { sError(); }
        else if (match('e')) {
            next();
            s4();
        }
        else { sError(); }
    }
    void s4() {
        if (endOfFile()) { sError(); }
        else if (match('m')) {
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


#endif //LAB1_SCHEMESAUTOMATON_H