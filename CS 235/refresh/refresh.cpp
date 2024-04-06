#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "argc: " << argc << " argv[0]: " << argv[0] << " argv [1]: " << argv[1] << endl;
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;

    }
    else {
        ifstream filehandle (argv[1]);
        if (!filehandle.is_open()){
            cout << "Could not open file" << endl;
        }
        else {
            string name;
            int age;
            while (filehandle >> name >> age){
                cout << "Name: " << name << "Age: " << age << endl;
            }
        }
    }
};