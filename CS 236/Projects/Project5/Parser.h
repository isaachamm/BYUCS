//
// Created by Isaac Hamm on 6/30/22.
//

#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H

#include "Token.h"
#include <vector>
#include <iostream>
#include "DatalogProgram.h"

using namespace std;


class Parser {

private:
    vector<Token> tokens;
    unsigned int currTokenIndex = 0;
    DatalogProgram program;

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
        Predicate newScheme;

        match(ID);
        newScheme.setName(getPrevTokenContents());

        match(LEFT_PAREN);
        match(ID);
        newScheme.addParameter(getPrevTokenContents());

        idList(newScheme);

        match(RIGHT_PAREN);
        program.addScheme(newScheme);
    }

    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD (passed)
    void fact() {
        Predicate newFact;

        match(ID);
        newFact.setName(getPrevTokenContents());

        match(LEFT_PAREN);
        match(STRING);
        newFact.addParameter(getPrevTokenContents());
        program.addDomain(getPrevTokenContents());

        stringList(newFact);
        match(RIGHT_PAREN);
        match(PERIOD);

        program.addFact(newFact);
    }

    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD (passed)
    void rule() {
        Rule newRule;
        Predicate firstPredicate;
        Predicate predicateToAdd;

        headPredicate(firstPredicate);
        newRule.setHead(firstPredicate);

        match(COLON_DASH);
        predicate(predicateToAdd);
        newRule.addPredicate(predicateToAdd);

        predicateList(newRule);
        match(PERIOD);

        program.addRule(newRule);
    }

    // query -> predicate Q_MARK (passed)
    void query() {
        Predicate newQuery;

        predicate(newQuery);
        match(Q_MARK);

        program.addQuery(newQuery);
    }

    // headPredicate ->	ID LEFT_PAREN ID idList RIGHT_PAREN (passed)
    void headPredicate(Predicate& addPredicate) {
        match(ID);
        addPredicate.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        match(ID);
        addPredicate.addParameter(getPrevTokenContents());
        idList(addPredicate);
        match(RIGHT_PAREN);
    }

    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN (passed)
    void predicate(Predicate& predicateToAdd) {
        match(ID);
        predicateToAdd.setName(getPrevTokenContents());

        match(LEFT_PAREN);
        parameter();
        predicateToAdd.addParameter(getPrevTokenContents());

        parameterList(predicateToAdd);
        match(RIGHT_PAREN);
    }

    // predicateList ->	COMMA predicate predicateList | lambda (passed)
    void predicateList(Rule& ruleToAdd) {
        if (currTokenType() == COMMA) {
            match(COMMA);

            Predicate predicateToAdd;
            predicate(predicateToAdd);
            ruleToAdd.addPredicate(predicateToAdd);

            predicateList(ruleToAdd);
        }
        else {
            //lambda
        }
    }

    // parameterList -> COMMA parameter parameterList | lambda (passed)
    void parameterList(Predicate& predicateToAdd) {
        if(currTokenType() == COMMA) {
            match(COMMA);
            parameter();
            predicateToAdd.addParameter(getPrevTokenContents());
            parameterList(predicateToAdd);
        }
        else {
            //lambda
        }
    }

    // stringList -> COMMA STRING stringList | lambda (passed)
    void stringList(Predicate& predicateToAdd) {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            predicateToAdd.addParameter(getPrevTokenContents());
            program.addDomain(getPrevTokenContents());
            stringList(predicateToAdd);
        } else {
            // lambda
        }
    }

    //   idList -> COMMA ID idList | lambda (passed)
    void idList(Predicate& predicateToAdd) {
        if (currTokenType() == COMMA) {
            match(COMMA);
            match(ID);
            predicateToAdd.addParameter(getPrevTokenContents());
            idList(predicateToAdd);
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

    DatalogProgram run() {
        datalogProgram();
        return program;
    }

    string getPrevTokenContents() {
        if (currTokenIndex < 0) throw "Tried to read when empty";
        return tokens.at(currTokenIndex - 1).getContents();
    }

    string getCurrTokenContents() {
        if (currTokenIndex >= tokens.size()) throw "Tried to go past token size";
        return tokens.at(currTokenIndex).getContents();
    }



};


#endif //LAB1_PARSER_H
