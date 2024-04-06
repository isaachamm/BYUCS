//
// Created by Isaac Hamm on 6/25/22.
//

#ifndef LAB1_UNDEFINEDBLOCKCOMMENTAUTOMATON_H
#define LAB1_UNDEFINEDBLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class UndefinedBlockCommentAutomaton : public Automaton {

public:
    UndefinedBlockCommentAutomaton() {
        type = TokenType::UNDEFINED;
    }

private:
    void s0() {
        if(match('#')) {
            next();
            s1();
        }
        else sError();
    }
    void s1() {
        if (endOfFile()) sError();
        else if(match('|')) {
            next();
            s2();
        }
        else sError();
    }
    void s2() {
        if (endOfFile()) return;
        else if (match('|')) {
            next();
            s3();
        }
        else {
            next();
            s2();
        }
    }
    void s3() {
        if (endOfFile()) return;
        else if (match('#')) {
            next();
            return;
        }
        else {
            next();
            s2();
        }
    }



};


#endif //LAB1_UNDEFINEDBLOCKCOMMENTAUTOMATON_H