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

vector<string> lexer(ifstream *file) {
    string line;
    vector<string> tokens;
    int i = 0;
    bool ignoreComma = false;
    while (getline(*file, line)) {
        string token = "";
        for (char c:line) {
            //token += c;
            if (c != '(' && c != ',' && c != ' ' && c != ')') {
                token += c;
            } else {
                if (c == ',' && ignoreComma) {
                    token += c;
                    continue;
                }
                tokens.push_back(token);
                token = "";
                i++;
                if (c == '(') {
                    ignoreComma = true;
                } else if (c == ')') {
                    ignoreComma = false;
                }
            }
        }
    }

    return tokens;
}