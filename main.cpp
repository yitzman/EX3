#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <array>
#include <vector>


using namespace std;

vector<string> lexer(ifstream *);


int main(int argv, char *argc[]) {
    string *strArr;
    ifstream file;
    file.open(argc[1]);
    vector<string> tokens = lexer(&file);
    for (string token:tokens)
        cout << token << endl;
    file.close();
    return 0;
}

