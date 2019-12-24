//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_INTERPRETER_H
#define UNTITLED_INTERPRETER_H

#include <queue>
#include <map>
#include "Expression.h"

class Interpreter {
public:
    Interpreter();
    map<string,string> varMap;
    Expression *interpret(string);

    void setVariables(string);

};


#endif //UNTITLED_INTERPRETER_H
