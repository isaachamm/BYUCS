//
// Created by Isaac Hamm on 6/30/22.
//

#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H

#include "Token.h"
#include <vector>
#include <iostream>

using namespace std;


class Parser {

private:
    vector<Token> tokens;
    unsigned int currTokenIndex = 0;

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}


    //todo move these three functions to private after the lab testing
    TokenType currTokenType() const {
        if (currTokenIndex >= tokens.size()) return UNDEFINED;
        return tokens.at(currTokenIndex).getType();
    }

    void advanceToken() {
        ++currTokenIndex;
    }

    void throwError() {
        if (currTokenIndex >= tokens.size()) throw tokens.at(tokens.size() - 1);
        throw tokens.at(currTokenIndex);
    }

    void match(TokenType expectedType) {
        //todo the cout should be removed for the final project output
//        cout << "Token at index " << currTokenIndex << " was type: " << typeName(currTokenType()) << " expected: " << typeName(expectedType) << endl;
        if (currTokenType() == expectedType) {
            advanceToken();
        } else {
            throwError();
        }
    }

    //Each nonterminal gets its own function here
    //this is the grammar section

    //datalogProgram ->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON
    //      query queryList EOF
    void datalogProgram() {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(EOFTOKEN);
    }

    // schemeList -> scheme schemeList | lambda
    void schemeList() {
        if (currTokenType() == ID) {
            scheme();
            schemeList();
        }
        else {
            //lambda
        }
    }

    // factList	-> fact factList | lambda
    void factList() {
        if (currTokenType() == ID) {
            fact();
            factList();
        }
        else {
            //lambda
        }
    }

    // ruleList	-> rule ruleList | lambda
    void ruleList() {
        if (currTokenType() == ID) {
            rule();
            ruleList();
        }
        else {
            //lambda
        }
    }

    // queryList -> query queryList | lambda (passed)
    void queryList() {
        if (currTokenType() == ID) {
            query();
            queryList();
        }
        else {
            //lambda
        }
    }

    //    scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN (passed)
    void scheme() {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }

    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD (passed)
    void fact() {
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }

    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD (passed)
    void rule() {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }

    // query -> predicate Q_MARK (passed)
    void query() {
        predicate();
        match(Q_MARK);
    }

    // headPredicate ->	ID LEFT_PAREN ID idList RIGHT_PAREN (passed)
    void headPredicate() {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }

    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN (passed)
    void predicate() {
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
    }

    // predicateList ->	COMMA predicate predicateList | lambda (passed)
    void predicateList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            predicate();
            predicateList();
        }
        else {
            //lambda
        }
    }

    // parameterList -> COMMA parameter parameterList | lambda (passed)
    void parameterList() {
        if(currTokenType() == COMMA) {
            match(COMMA);
            parameter();
            parameterList();
        }
        else {
            //lambda
        }
    }

    // stringList -> COMMA STRING stringList | lambda (passed)
    void stringList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            stringList();
        } else {
            // lambda
        }
    }

    //   idList -> COMMA ID idList | lambda (passed)
    void idList() {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        } else {
            // lambda
        }
    }

    // parameter ->	STRING | ID (passed)
    void parameter() {
        if(currTokenType() == STRING) {
            match(STRING);
        }
        else {
            match(ID);
        }
    }

    //write a run function - should call datalog program (the first thing in our grammar)

//    void datalogProgram() {}

    void run() {
        datalogProgram();
    }



};


#endif //LAB1_PARSER_H
