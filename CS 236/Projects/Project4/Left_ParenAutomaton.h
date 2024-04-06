//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_LEFT_PARENAUTOMATON_H
#define LAB1_LEFT_PARENAUTOMATON_H


#include "Automaton.h"

class Left_ParenAutomaton : public Automaton {

public:
    Left_ParenAutomaton() {
        type = TokenType::LEFT_PAREN; // set the type
    }

private:
    void s0() {
        if (match('(')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};


#endif //LAB1_LEFT_PARENAUTOMATON_H
