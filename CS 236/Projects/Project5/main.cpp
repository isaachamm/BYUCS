#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Relation.h"
#include "Interpreter.h"

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

    DatalogProgram datalog;

        try {
            Parser parser = Parser(tokens);
            datalog = parser.run();
//            cout << "Success!" << endl;
//            cout << datalog.toString();
        }
        catch(Token errorToken) {
            cout << "Failure!" << endl << "  " << errorToken.toString();
        }
        catch(const char* errorMsg) {
            cout << errorMsg;
        }

        Interpreter interpreter(datalog);
        interpreter.run();


//

    return 0;
}