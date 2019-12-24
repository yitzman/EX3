#include <iostream>
#include <vector>

#include "Lexer.h"
#include "Command.h"
#include "Interpreter/ex1.h"
//#include "tester5/Parser.h"
using namespace std;

vector<string> getVariables(string exp);

int main(int argv, char *argc[]) {
    /*
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
    file.close();*/


    map<string, int> varMap;
    varMap.insert({"heading", 200});
    varMap.insert({"h0", 40});
    varMap.insert({"rpm",5});

    Interpreter *i = new Interpreter();
    vector<string> variables = getVariables("  rpm+");
    Interpreter *intrptr = new Interpreter();
    for (string s : variables) {
        intrptr->setVariables(s + "=" + to_string(varMap[s]));
    }
    Expression *e = intrptr->interpret("   rpm");

    cout << e->calculate();

    return 0;
}

vector<string> getVariables(string exp) {
    vector<string> variables;
    string token = "";
    for (char c: exp) {
        if (c == ' ' || c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c == ')') {
            if (token != "" && token != "\t")
                variables.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }
    if(token != "" && token !="\t")
        variables.push_back(token);
    return variables;
}