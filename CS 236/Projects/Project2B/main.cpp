#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Relation.h"

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

        try {
            Parser parser = Parser(tokens);
            DatalogProgram test = parser.run();
            cout << "Success!" << endl;
            cout << test.toString();
        }
        catch(Token errorToken) {
            cout << "Failure!" << endl << "  " << errorToken.toString();
        }
        catch(const char* errorMsg) {
            cout << errorMsg;
        }



    return 0;
}

//int main() {
//    DatalogProgram program;
//
//    Predicate snapScheme;
//    snapScheme.setName("snap");
//    snapScheme.addParameter("S");
//    snapScheme.addParameter("N");
//    snapScheme.addParameter("A");
//    snapScheme.addParameter("P");
//
//    program.addScheme(snapScheme);
//
//    Predicate addressScheme;
//    addressScheme.setName("HasSameAddress");
//    addressScheme.addParameter("X");
//    addressScheme.addParameter("Y");
//    program.addScheme(addressScheme);
//
//    Predicate snapFact;
//    snapFact.setName("snap");
//    snapFact.addParameter("\'12345\'");
//    snapFact.addParameter("\'C. Brown\'");
//    snapFact.addParameter("\'12 Apple\'");
//    snapFact.addParameter("\'555-1234\'");
//    program.addFact(snapFact);
//
//    Rule thisRule;
//    thisRule.setHead(addressScheme);
//    thisRule.addPredicate(snapScheme);
//    thisRule.addPredicate(snapScheme);
//    program.addRule(thisRule);
//
//    Predicate addressQuery;
//    addressQuery.setName("HasSameAddress");
//    addressQuery.addParameter("\'Snoopy\'");
//    addressQuery.addParameter("Who");
//    program.addQuery(addressQuery);
//
//
//    cout << program.toString();
//    return 0;
//}