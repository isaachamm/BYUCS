#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    string name;
    if (argc > 1) {
        name = argv[1];
    } else {
        name = "World!";
    }
    cout << "Hello " << name << endl;
}