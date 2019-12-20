//
// Created by avi on 19/12/2019.
//

#ifndef MILESTONE1_LEXER_H
#define MILESTONE1_LEXER_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;
class Lexer {
public:
    Lexer();
    static vector<string> CutLine(string line);
    static vector<vector<string>> cutFile(ifstream *file);
};


#endif //MILESTONE1_LEXER_H
