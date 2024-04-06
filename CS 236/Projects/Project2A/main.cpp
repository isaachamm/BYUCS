#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[]) {

    //Uncomment this after testing
    Lexer lexer;
    ifstream inputFile;
    string inputText;
    inputFile.open(argv[1]);
    if (inputFile.is_open()) {
        string line;
        while(getline(inputFile, line)) {
            inputText += (line + '\n');
        }
    }
    inputFile.close();
    vector<Token> tokens = lexer.run(inputText); //– this returns a vector of tokens, pass this to parser

//    cout << "Total Tokens = " << lexer.getTokens().size();
//Until here

//        vector<Token> tokens = {
////                Token(,",",2),
//                Token(ID,"predicate",2),
//                Token(LEFT_PAREN,"(",2),
//                Token(STRING,"string",2),
//                Token(COMMA,",",2),
//                Token(STRING,"ID",2),
//                Token(COMMA,",",2),
//                Token(ID, "STRING BABY",2),
////                Token(COMMA,")",2),
//                Token(RIGHT_PAREN,",",3),
//
//                Token(Q_MARK,"predicate",2),
//
//                Token(ID,"predicate",2),
//                Token(LEFT_PAREN,"(",2),
//                Token(STRING,"string",2),
//                Token(COMMA,",",2),
//                Token(STRING,"ID",2),
//                Token(COMMA,",",2),
//                Token(ID, "STRING BABY",2),
////                Token(COMMA,")",2),
//                Token(RIGHT_PAREN,",",3),
//
//                Token(RIGHT_PAREN,"predicate",7),
//        };

        try {
            Parser parser = Parser(tokens);
            parser.run();
            cout << "Success!";
        }
        catch(Token errorToken) {
            cout << "Failure!" << endl << "  " << errorToken.toString();
        }


    return 0;
}
