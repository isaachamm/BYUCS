//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_MULTIPLYAUTOMATON_H
#define LAB1_MULTIPLYAUTOMATON_H


#include "Automaton.h"

class MultiplyAutomaton : public Automaton {

public:
    MultiplyAutomaton() {
        type = TokenType::MULTIPLY; // set the type
    }

private:
    void s0() {
        if (match('*')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};


#endif //LAB1_MULTIPLYAUTOMATON_H
