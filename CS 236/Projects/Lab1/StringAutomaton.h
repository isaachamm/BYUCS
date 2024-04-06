//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_STRINGAUTOMATON_H
#define LAB1_STRINGAUTOMATON_H

#include "Automaton.h"

using namespace std;

class StringAutomaton : public Automaton {

public:
    StringAutomaton() {
        type = TokenType::STRING;
    }

private:
    void s0() {
        if (match('\'')) {
            next();
            s1();
        }
        else sError();
    }
    void s1() {
        if (endOfFile()) { sError(); }
        else if (match('\'')) {
            next();
            s2();
        }
        else {
            next();
            s1();
        }
    }
    void s2() {
        if (endOfFile()) { return; }
        else if (match('\'')) {
            next();
            s1();
        }
        else {
            return;
        }
    }

};


#endif //LAB1_STRINGAUTOMATON_H
