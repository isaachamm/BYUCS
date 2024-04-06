//
// Created by Isaac Hamm on 6/25/22.
//

#ifndef LAB1_SINGLELINECOMMENTAUTOMATON_H
#define LAB1_SINGLELINECOMMENTAUTOMATON_H

#include "Automaton.h"

using namespace std;

class SingleLineCommentAutomaton : public Automaton {

public:
    SingleLineCommentAutomaton() {
        type = TokenType::COMMENT;
    }

private:
    void s0() {
        if (match('#')) {
            if (input.at(currCharIndex + 1) == '|') {
                    sError();
            }
            else {
                next();
                s1();
            }
        }
        else sError();
    }
    void s1() {
        if (endOfFile()) { return; }
        else if (match('\n')) {
            return;
        }
        else {
            next();
            s1();
        }
    }
};


#endif //LAB1_SINGLELINECOMMENTAUTOMATON_H
