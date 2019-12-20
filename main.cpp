#include <iostream>
#include <fstream>
#include <array>
#include <vector>

#include "Lexer.h"
#include "Command.h"

using namespace std;

int main(int argv, char *argc[]) {
    string *strArr;
    ifstream file;
    file.open(argc[1]);
    vector<vector<string>> vectors = Lexer::cutFile(&file);
    for (vector<string> tokens:vectors) {
        int i = 1;
        for (string token: tokens) {
            cout << i << ")" + token << "\t";
            i++;
        }
        cout << "\n";
    }
    file.close();
    return 0;
}

