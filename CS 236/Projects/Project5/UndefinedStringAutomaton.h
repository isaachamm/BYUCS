//
// Created by Isaac Hamm on 6/25/22.
//

#ifndef LAB1_UNDEFINEDSTRINGAUTOMATON_H
#define LAB1_UNDEFINEDSTRINGAUTOMATON_H


#include <iostream>
#include "Automaton.h"

using namespace std;

class UndefinedStringAutomaton : public Automaton {

public:
    UndefinedStringAutomaton() {
        type = TokenType::UNDEFINED;
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
        if (endOfFile()) { return; }
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


#endif //LAB1_UNDEFINEDSTRINGAUTOMATON_H
