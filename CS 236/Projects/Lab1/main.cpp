#include <iostream>
#include <fstream>
#include <sstream>
#include "Token.h"
#include "Lexer.h"

//Note: there should be 17 automaton-type files (+EOF)

using namespace std;

int main(int argc, char* argv[]) {

    Lexer lexer;
    ifstream inputFile;
    stringstream sstream;
    string inputText;
    inputFile.open(argv[1]);
    if (inputFile.is_open()) {
        string line;
        //todo put inputfile into variable input and pass to lexer.run
        while(getline(inputFile, line)) {
//            cout << line << endl;
            inputText += (line + '\n');
        }
    }
    inputFile.close();

    lexer.run(inputText);


    //Testing that toString and Token class both work (passed)
//    Token myToken = Token(COMMA, ",", 42);
//    cout << myToken.toString() << endl;
//    cout << endl;

//Testing the ColonAutomaton (passed)
//    lexer.run(":::\n\n");

//Testing all other automaton (passed)
//    lexer.run("::-myPerson\n");
//    lexer.run("::-myPer son:  111  23:   :-:@");

//Testing a comma (passed)
//    lexer.run("Hello, I, am,\n");

//testing period (passed)
//    lexer.run("Heyo.. what's.");

//testing ? (passed)
//    lexer.run("? what's in the \nmiddle ??");

//Testing () (passed)
//    lexer.run("() ) ()( ))");

//Testing * (passed)
//    lexer.run("***");

//Testing + (passed)
//    lexer.run("+++");
//just for fun
//    lexer.run("+* ASd F %$# %$+^&*()&( \n *(_");


    //Testing a blank (empty) string -- do we have to do something with this?
//    lexer.run("");

//Testing Schemes (passed)
//    lexer.run("Schemes");
//    lexer.run("Schemess");
//    lexer.run("SSchemes");

//Testing Facts (passed)
//    lexer.run("Facts");
//    lexer.run("Factsss");
//    lexer.run("FFacts");

//Testing Rules (passed)
//    lexer.run("Rules");
//    lexer.run("Rulesss");
//    lexer.run("RRules");

//Testing queries (passed)
//    lexer.run("Queries");
//    lexer.run("Queriesss");
//    lexer.run("QQueries");

//Testing string (passed?)
//    lexer.run("'I don''t know what I''m doing");
//    lexer.run("'I don''t know what I''m doing'\n 'another string'");

//Testing linecomment (passed?)
//    lexer.run("#This is a comment...");
//    lexer.run("#| This should be a \n Block comment |# a");
//    lexer.run("#| This should be a \n UNDEF Block comment | # a");

//    lexer.run("'this is a bad string \n \n \n \n");

//    lexer.run("#||# abcd");
//    lexer.run("#||##||# Rules:");




    //TODO final output line is "Total Tokens = N
    //I think this works now, test more extensively...
    cout << "Total Tokens = " << lexer.getTokens().size();

    return 0;
}
