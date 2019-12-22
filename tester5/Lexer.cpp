//
// Created by avi on 19/12/2019.
//

#include <algorithm>
#include "Lexer.h"


vector<vector<string>> Lexer::cutFile(fstream *file) {
    vector<vector<string>> vectors;
    string line;
    vector<string> tokens;

    while (getline(*file, line)) {
        tokens = CutLine(line);
        vectors.push_back(tokens);
    }
    return vectors;
}

vector<string> Lexer::CutLine(string line) {
    vector<string> tokens;
    string token = "";
    bool ignoreInBracket = false, ignoreForLine = false;
    int i = 0;
    for (char c:line) {
        i++;
        if (c == ' ' && !ignoreInBracket && !ignoreForLine) {
            if (token != "") {
                tokens.push_back(token);
                token = "";
            }
            continue;
        }
        if (c == '=') {
            if (token == ">" ||token == "<") {
                token += c;
                tokens.push_back(token);
            } else if (token != "") {
                tokens.push_back(token);
                token = c;
                tokens.push_back(token);
            } else {
                tokens.push_back(token = c);
            }
            ignoreForLine = true;
            token = "";
            continue;
        }
        if (c == '(' && !ignoreForLine) {
            tokens.push_back(token);
            token = "";
            ignoreInBracket = true;
            continue;
        }
        if (c == ')' && !ignoreForLine) {
            tokens.push_back(token);
            token = "";
            ignoreInBracket = false;
            continue;
        }
        if (c == '-' && !ignoreForLine && !ignoreInBracket) {
            if (token == "") {
                token = c;
            } else if (token == "<") {
                token += c;
                tokens.push_back(token);
                token = "";
            } else {
                tokens.push_back(token);
                token = c;
            }
            continue;
        }
        if (c == '{') {
            if (token != "")
                tokens.push_back(token);
            token = c;
            tokens.push_back(token);
            continue;
        }
        if (c == '}') {
            tokens.push_back(token = c);
            continue;
        }
        if (c == '<') {
            if (token != "")
                tokens.push_back(token);
            token = c;
            continue;
        }
        if (c == '>') {
            if(token == "-"){
                token+=c;
                tokens.push_back(token);
                token="";
                continue;
            }
            if (token != "")
                tokens.push_back(token);
            token = c;
            continue;
        }
        if (i == line.length()) {
            token += c;
            tokens.push_back(token);

            continue;
        }
        if(c!='\t') {
            token += c;
        }
    }
    return tokens;
}

Lexer::Lexer() {}

