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

    DatalogProgram dataTest;

    //This is testing for Proj3
//    Predicate schemeTest;
//    schemeTest.setName("snap");
//    schemeTest.addParameter("S");
//    schemeTest.addParameter("N");
//    schemeTest.addParameter("A");
//    schemeTest.addParameter("P");
//    dataTest.addScheme(schemeTest);
//
//    Predicate testScheme;
//    testScheme.setName("spa");
//    testScheme.addParameter("S");
//    testScheme.addParameter("P");
//    testScheme.addParameter("A");
//    dataTest.addScheme(testScheme);
//
//    Predicate factTest;
//    factTest.setName("snap");
//    factTest.addParameter("Hello");
//    factTest.addParameter("Hi");
//    factTest.addParameter("Heyo");
//    factTest.addParameter("Hey");
//    dataTest.addFact(factTest);
//
//    Predicate testFact;
//    testFact.setName("spa");
//    testFact.addParameter("\'Yo\'");
//    testFact.addParameter("\'Yoyo\'");
//    dataTest.addFact(testFact);
//
//    Predicate testFact1;
//    testFact1.setName("spa");
//    testFact1.addParameter("\'Holla\'");
//    testFact1.addParameter("\'Holla\'");
//    dataTest.addFact(testFact1);
//
//    Predicate testQuery;
//    testQuery.setName("spa");
//    testQuery.addParameter("\'Hey\'");
//    testQuery.addParameter("\'Hi\'");
//    dataTest.addQuery(testQuery);
//
//    Predicate queryTest;
//    queryTest.setName("spa");
//    queryTest.addParameter("y");
//    queryTest.addParameter("z");
//    dataTest.addQuery(queryTest);
//
//    Database database;
//    Interpreter test(dataTest, database);
//
//    test.evalSchemes();
//    test.evalFacts();
//    test.evalQueries();


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

    DatalogProgram test;

        try {
            Parser parser = Parser(tokens);
            test = parser.run();
//            cout << "Success!" << endl;
//            cout << test.toString();
        }
        catch(Token errorToken) {
            cout << "Failure!" << endl << "  " << errorToken.toString();
        }
        catch(const char* errorMsg) {
            cout << errorMsg;
        }

        Interpreter interpreter(test);
        interpreter.run();




    return 0;
}