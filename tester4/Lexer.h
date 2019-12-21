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
    vector<string> CutLine(string line);
    vector<vector<string>> cutFile(fstream fs);
    vector<string> cutIfCommand(string str);
};


#endif //MILESTONE1_LEXER_H
