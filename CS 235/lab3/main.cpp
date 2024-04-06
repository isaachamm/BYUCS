//
// Created by Isaac Hamm on 1/28/22.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> tokens;
    set<string> unique;
    string nextLine;
    ifstream in(argv[1]);

    while (getline(in, nextLine)) {         //reads in lines from file
        istringstream iss(nextLine);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for (auto& c : token) {
                if (isalpha(c)){
                    nopunct += c;
                }
            }
            tokens.push_back(nopunct);
            unique.insert(nopunct);
        }
    }

    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;

//    for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) {  //This loop prints the set to the terminal
//        cout << ' ' << *it;
//        cout << endl;
//    }

    string filename = argv[2];                          //Assigns the third terminal command as the name of the output file.

    string setFile = filename + "_set.txt";
    ofstream outFile_1(setFile);
    if (outFile_1.is_open()) {
        for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) {
            outFile_1 << *it << endl;
        }
    }
    else {
        cout << "could not open set file." << endl;
    }

    string vectorFile = filename + "_vector.txt";
    ofstream outFile_2(vectorFile);              //Assigns the third terminal command as the name of the output file.
    if (outFile_2.is_open()) {
        for (int i = 0; i < tokens.size(); ++i) {
            outFile_2 << tokens.at(i) << endl;
        }
    }
    else {
        cout << "could not open vector file" << argv[2] << endl;
    }

//    map <string, string> wordmap;           //creates a map with each word pointing to the next word
//    string last ="";
//    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); ++it) {
//        wordmap[last] = *it;
//        last = *it;
//    }

//creates a BETTER map with each word pointing to a vector of words
/*    map<string, vector<string> > wordmap;
    string last="";
    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it){
        wordmap[last].push_back(*it);
        last = *it;
    }
*/

//Creates an EVEN BETTER map with a list of words pointing to a vector of strings
    map<list<string>, vector<string> > wordmap;
    list<string> state;
    int M = 3;
    for (int i = 0; i < M; ++i) {
        state.push_back("");
    }

    for (vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        wordmap[state].push_back(*it);
        state.push_back(*it);
        state.pop_front();
    }

    srand(time(NULL));

    state.clear();
    for (int i = 0; i < M; ++i) {
        state.push_back("");
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            int ind = rand() % wordmap[state].size();
            cout << wordmap[state][ind] << " ";
            state.push_back(wordmap[state][ind]);
            state.pop_front();
        }
        cout << endl;
    }


//This is for printing values from a key to a vector of values
/*    string state="";
    for (int i = 0; i < 100; ++i) {
        int ind = rand() %wordmap[state].size();
        cout << wordmap[state].at(ind) << " ";
        state = wordmap[state].at(ind);
    }
*/

    /*–This is for printing the values of a specific key
    for (map<string, vector<string> >::iterator it = wordmap.begin(); it != wordmap.end(); ++it) {
        if (it->first == "Nephi") {
            for (int i = 0; i < it->second.size(); ++i) {
                cout << it->second.at(i) << ", ";
            }

                break;
        }
    }
*/
    //Writing to a file w/out vector
//    string mapFile = filename + "_map.txt";
//    ofstream outFile_3(mapFile);
//    if (outFile_3.is_open()) {                          //Prints out map key and value together
//        for (map<string, vector<string> >::iterator it = wordmap.begin(); it!=wordmap.end(); ++it) {
//
//            outFile_3 << it->first << ", " << it->second.at(1) << endl;
//        }
//    }
//    else {
//        cout << "could not open map file" << endl;
//    }

//Old way of printing out map w/o vector
//    string state = "";
//    for (int i = 0; i < 100; ++i) {
//        cout << wordmap[state] << " ";
//        state = wordmap[state];
//    }
//    cout << endl;


    return 0;
}





/*
    string fileName = argv[1];
    set<string> inputWords;

    ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        int c;
        string nextWord;
        while (!inputFile.eof()) {
            inputFile >> nextWord;

            for (int i = 0; i < nextWord.size(); ++i){
                c = nextWord.at(i);
                if (!(isalpha(nextWord.at(i))) || !(nextWord.at(i) == ' ')) {
                    nextWord.erase(c);
                }
            }
            inputWords.insert(nextWord);
        }
    }
    else {
        cout << "could not open input file" << endl;
    }

    string output;

    for (auto& output:inputWords) {
        cout << output << endl;
    }

    return 0;
}*/