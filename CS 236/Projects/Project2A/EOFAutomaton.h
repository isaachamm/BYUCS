//
// Created by Isaac Hamm on 6/25/22.
//

#ifndef LAB1_EOFAUTOMATON_H
#define LAB1_EOFAUTOMATON_H

#include "Automaton.h"

class EOFAutomaton : public Automaton {

public:
    EOFAutomaton() {
        type = TokenType::EOFTOKEN;
    }

private:
    void s0() {
        if(input.size() == 0) {
            return;
        }
    }


};


#endif //LAB1_EOFAUTOMATON_H
