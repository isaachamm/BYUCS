//
// Created by Isaac Hamm on 6/23/22.
//

#ifndef LAB1_UNDEFINEDCHARACTERAUTOMATON_H
#define LAB1_UNDEFINEDCHARACTERAUTOMATON_H


#include "Automaton.h"

class UndefinedCharAutomaton : public Automaton {

public:
    UndefinedCharAutomaton() {
        type = TokenType::UNDEFINED; // set the type
    }

private:
    void s0() {
        next(); // read next character
        return; // accept the input
    }
};


#endif //LAB1_UNDEFINEDCHARACTERAUTOMATON_H
