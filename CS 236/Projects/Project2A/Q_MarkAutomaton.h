//
// Created by Isaac Hamm on 6/24/22.
//

#ifndef LAB1_Q_MARKAUTOMATON_H
#define LAB1_Q_MARKAUTOMATON_H


#include "Automaton.h"

class Q_MarkAutomaton : public Automaton {

public:
    Q_MarkAutomaton() {
        type = TokenType::Q_MARK; // set the type
    }

private:
    void s0() {
        if (match('?')) {
            next();
            return; // this represents accepting the input
        }
        else
            sError(); // this calls the error state
    }
};


#endif //LAB1_Q_MARKAUTOMATON_H
