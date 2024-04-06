//
// Created by Isaac Hamm on 6/23/22.
//

#ifndef LAB1_TOKEN_H
#define LAB1_TOKEN_H

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

enum TokenType {
    ADD, BLOCKCOMMENT, COLON, COLON_DASH, COMMA, COMMENT, EOFTOKEN, FACTS, ID, LEFT_PAREN, MULTIPLY, PERIOD, Q_MARK, QUERIES, RIGHT_PAREN,
        RULES, SCHEMES, SINGLELINECOMMENT, STRING, UNDEFINED, UNDEFINEDBLOCKCOMMENT, UNDEFINEDSTRING  //TODO: maybe need to separate strings and comments into different things
};

class Token {

private:
    TokenType type = UNDEFINED;
    string contents = "";
    unsigned int line = 0;

public:
    Token();
    Token(TokenType toktype, string letters, unsigned int num) : type(toktype), contents(letters), line(num) {}


    //getter functions
    TokenType getType() const {
        return type;
    }

    const string &getContents() const {
        return contents;
    }

    // Returns the name of the token type instead of the number
    string typeName(TokenType type) const {
        switch (type) {
            case ADD:
                return "ADD";
            case BLOCKCOMMENT:
                return "BLOCKCOMMENT";
            case COMMA:
                return "COMMA";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case COMMENT:
                return "COMMENT";
            case EOFTOKEN:
                return "EOF";
            case FACTS:
                return "FACTS";
            case ID:
                return "ID";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case MULTIPLY:
                return "MULTIPLY";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case QUERIES:
                return "QUERIES";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case RULES:
                return "RULES";
            case SCHEMES:
                return "SCHEMES";
            case SINGLELINECOMMENT:
                return "SINGLELINECOMMENT";
            case STRING:
                return "STRING";
            case UNDEFINED:
                return "UNDEFINED";
            case UNDEFINEDBLOCKCOMMENT:
                return "UNDEFINEDBLOCKCOMMENT";
            case UNDEFINEDSTRING:
                return "UNDEFINEDSTRING";
            default:
                return "Undefined Token: ADD TO TOKENTYPE";

        }
    }

    string toString() const {
        stringstream output;
        output << "(" << typeName(type) << "," << "\"" << contents << "\"" << "," << line << ")";
        return output.str();
    }



};


#endif //LAB1_TOKEN_H
