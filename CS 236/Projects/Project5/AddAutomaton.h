//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_ADDAUTOMATON_H
#define LAB1_ADDAUTOMATON_H


#include "Automaton.h"

class AddAutomaton : public Automaton {

public:
    AddAutomaton() {
        type = TokenType::ADD; // set the type
    }

private:
    void s0() {
        if (match('+')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};


#endif //LAB1_ADDAUTOMATON_H
