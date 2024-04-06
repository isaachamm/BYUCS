//
// Created by Isaac Hamm on 6/23/22.
//

#ifndef LAB1_LEXER_H
#define LAB1_LEXER_H

#include <vector>
#include "Token.h"
#include "Automaton.h"

#include "AddAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "EOFAutomaton.h"
#include "FactsAutomaton.h"
#include "IDAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "QueriesAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "SingleLineCommentAutomaton.h"
#include "StringAutomaton.h"
#include "UndefinedBlockCommentAutomaton.h"
#include "UndefinedCharacterAutomaton.h"
#include "UndefinedStringAutomaton.h"

using namespace std;

class Lexer {

private:
    vector<Token> tokens;
    vector<Automaton*> automata;
    unsigned int currLine = 1; //1 because there's no 0 line in a file

public:

    vector<Token> getTokens() const {
        return tokens;
    }

    void initializeAutomata() {
        //order matters here
        //earlier in the list = higher precedence when both return the same value
        automata.push_back(new AddAutomaton());
        automata.push_back(new ColonAutomaton());
        automata.push_back(new CommaAutomaton());
        automata.push_back(new ColonDashAutomaton());
        automata.push_back(new Left_ParenAutomaton());
        automata.push_back(new MultiplyAutomaton());
        automata.push_back(new PeriodAutomaton());
        automata.push_back(new Q_MarkAutomaton());
        automata.push_back(new Right_ParenAutomaton());

        //Keyword automata
        automata.push_back(new SchemesAutomaton());
        automata.push_back(new FactsAutomaton());
        automata.push_back(new RulesAutomaton());
        automata.push_back(new QueriesAutomaton());

        //Other Automata
        automata.push_back(new StringAutomaton());
        automata.push_back(new UndefinedStringAutomaton());
        automata.push_back(new BlockCommentAutomaton());
        automata.push_back(new SingleLineCommentAutomaton());
        automata.push_back(new UndefinedBlockCommentAutomaton());

        //This one has to be below all keywords
        automata.push_back(new IDAutomaton());

        //Always keep unidentified on the bottom of this list
        automata.push_back(new UndefinedCharAutomaton());

        //has to be last to run at the end
        automata.push_back(new EOFAutomaton());
    }

    vector<Token> run(string input) {
        initializeAutomata();
        //parrallel and max logic
        while (input.size() > 0) {
            Automaton *maxAutomaton = automata.at(0);
            unsigned int maxRead = 0;

            //handle whitespace -- have to add to currLine for newlines, skip everything else
            if (isspace(input.at(0))) {
                if (input.at(0) == '\n') {       //adds to currLine for newline characters
                    currLine++;
                }
                input = input.substr(1); // this is to delete the whitespace character and then continue
                continue;
            }

            for (Automaton *iterator: automata) {      //foreach loop to go through each automaton
                Automaton *currAutomaton = iterator;
                unsigned int currCharRead = currAutomaton->run(input);
                if (currCharRead > maxRead) {
                    maxRead = currCharRead;
                    maxAutomaton = currAutomaton;
                }
            }

            //Count newlines – I think this will work, need to test more extensively, especially with
            Token currToken = Token(maxAutomaton->getType(), input.substr(0, maxRead),
                                    currLine/*defaults to 0, you will need to fix for the project*/);
            currLine += maxAutomaton->getNewLines();
            if (maxAutomaton->getType() != COMMENT) {
//                cout << currToken.toString() << endl;
                tokens.push_back(currToken);
            }
            input = input.substr(maxRead);
        }

        //run for EOF token
        if (input.size() == 0) {
            Token endToken = Token(EOFTOKEN, "", currLine);
//            cout << endToken.toString() << endl;
            tokens.push_back(endToken);
        }

        return tokens;
    }
};


#endif //LAB1_LEXER_H
