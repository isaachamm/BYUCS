#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    //characters to check: ()[]{}<>

    //outline:

    stack <char> parenthesisStack;          //Stack used to store parenthesis characters
//    string nextChar = (argc > 1) ? argv[1] : "Let's go";
    string nextChar = argv[1];

    /*  for (int i =0; i < nextChar.size(); ++i){
          cout << nextChar.at(i) << endl;
      }
  This is to test the input*/


    for (int i = 0; i < nextChar.size(); ++i) {
        if (parenthesisStack.empty()) {
            if (nextChar.at(i) == ')' || nextChar.at(i) == ']' || nextChar.at(i) == '}' ||  //This is to put a parenthesis in when the stack is empty
            nextChar.at(i) == '>' || nextChar.at(i) == '(' || nextChar.at(i) == '['||
            nextChar.at(i) == '{' || nextChar.at(i) == '<')
            parenthesisStack.push(nextChar.at(i));
        }
        else if (nextChar.at(i) == ')') {
            if (!parenthesisStack.empty()) {
                if (parenthesisStack.top() == '(') {
                    parenthesisStack.pop();
                } else {
                    parenthesisStack.push(nextChar.at(i));
                }
            }
        }
            else if (nextChar.at(i) == ']') {
            if (!parenthesisStack.empty()) {
                if (parenthesisStack.top() == '[') {
                    parenthesisStack.pop();
                } else {
                    parenthesisStack.push(nextChar.at(i));
                }
            }
        }
            else if (nextChar.at(i) == '}') {
            if (!parenthesisStack.empty()) {
                if (parenthesisStack.top() == '{') {
                    parenthesisStack.pop();
                } else {
                    parenthesisStack.push(nextChar.at(i));
                }
            }
        }
            else if (nextChar.at(i) == '>') {
            if (!parenthesisStack.empty()) {
                if (parenthesisStack.top() == '<') {
                    parenthesisStack.pop();
                } else {
                    parenthesisStack.push(nextChar.at(i));
                }
            }
        }
            else if (nextChar.at(i) == '(' || nextChar.at(i) == '[' || nextChar.at(i) == '{'
                               || nextChar.at(i) == '<') {
                parenthesisStack.push(nextChar.at(i));
            }

        }

    if (parenthesisStack.empty()){          //Could use boolean here
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }

    return 0;
}
