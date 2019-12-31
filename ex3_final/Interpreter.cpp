//
// Created by yitzi on 06/11/2019.
//

#include <string>
#include <stack>
#include <sstream>
#include <list>
#include <queue>
#include <iostream>
#include "Interpreter.h"
#include "Expression.h"
#include "Value.h"
#include "Div.h"
#include "Mul.h"
#include "Plus.h"
#include "Minus.h"
#include "UPlus.h"
#include "UMinus.h"

Interpreter::Interpreter() {
    map<string, string> varMap;
}

Expression *Interpreter::interpret(string exp) {
    //1) Divide into tokens
    string s = "";
    vector<string> tokens;
    for (char c : exp) {
        //if char is integer or decimal point, add to token
        if (((c >= 48 && c <= 57) || (c >= 97 && c <= 122)) || (c == '.' && (s.find(c) == string::npos))) {
            s += c;
            if (s == ".")
                throw "invalid token";
            //if char is operator or bracket or space, save token
        } else if (c == '/' || c == '+' || c == '-' || c == '*' || c == '(' || c == ')' || c == ' ') {
            if (s.back() == '.')
                throw "invalid token";
            if (s != "")
                tokens.insert(tokens.end(), s);
            if(c!= ' ') {
                s = c;
                tokens.insert(tokens.end(), s);
            }
            s = "";
        } else
            throw "invalid token";
    }
    //last token
    if (s.back() == '.')
        throw "invalid token";
    if (s != "")
        tokens.insert(tokens.end(), s);
    //return tokens;

    //2) Make output queue

    stack<string> opStack;
    queue<string> outputQue;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        //store operators
        if (tokens[i] == "+" || tokens[i] == "-") {
            if (i == 0 || tokens[i - 1] == "(") {
                if (tokens[i] == "+")
                    opStack.push("u+");
                else
                    opStack.push("u-");
            } else {
                while (!opStack.empty() &&
                       (opStack.top() == "*" || opStack.top() == "/" || opStack.top() == "+" || opStack.top() == "-" ||
                        opStack.top() == "u-" || opStack.top() == "u+")) {
                    outputQue.push(opStack.top());
                    opStack.pop();
                }
                opStack.push(tokens[i]);
            }
        } else if (tokens[i] == "*" || tokens[i] == "/") {
            while (!opStack.empty() &&
                   (opStack.top() == "/" || opStack.top() == "*" || opStack.top() == "u-" || opStack.top() == "u+")) {
                outputQue.push(opStack.top());
                opStack.pop();
            }
            opStack.push(tokens[i]);
        } else if (tokens[i] == "(") {
            opStack.push(tokens[i]);
        } else if (tokens[i] == ")") {
            while (opStack.top() != "(") {
                outputQue.push(opStack.top());
                opStack.pop();
                if (opStack.empty()) {
                    throw "invalid brackets";
                }
            }
            opStack.pop();
            //if operand:

            //if variable
        } else if (tokens[i].front() >= 97 && tokens[i].front() <= 122) {
            if (varMap.count(tokens[i])) {
                outputQue.push(varMap.at(tokens[i]));
            } else
                throw "illegal math expression";
        }
            //if regular number
        else
            outputQue.push(tokens[i]);
    }

    while (!opStack.empty()) {
        outputQue.push(opStack.top());
        opStack.pop();

    }

    //3) Create expressions
    stack<Expression *> expStack;
    double f;
    while (!outputQue.empty()) {
        if (outputQue.front() != "/" && outputQue.front() != "*" && outputQue.front() != "-" &&
            outputQue.front() != "+" && outputQue.front() != "u-" && outputQue.front() != "u+") {
            stringstream(outputQue.front()) >> f;
            expStack.push(new Value(f));
        } else {
            Expression *e = expStack.top();
            expStack.pop();
            if (outputQue.front() == "/") {
                Div *div = new Div(expStack.top(), e);
                expStack.pop();
                expStack.push(div);
            } else if (outputQue.front() == "*") {
                Mul *mul = new Mul(e, expStack.top());
                expStack.pop();
                expStack.push(mul);
            } else if (outputQue.front() == "+") {
                Plus *plus = new Plus(e, expStack.top());
                expStack.pop();
                expStack.push(plus);
            } else if (outputQue.front() == "-") {
                Minus *minus = new Minus(expStack.top(), e);
                expStack.pop();
                expStack.push(minus);
            } else if (outputQue.front() == "u+") {
                UPlus *uplus = new UPlus(e);
                expStack.push(uplus);
            } else if (outputQue.front() == "u-") {
                UMinus *uminus = new UMinus(e);
                expStack.push(uminus);
            }
        }
        outputQue.pop();
    }
    return expStack.top();
}

void Interpreter::setVariables(string variables) {
    string s = "", left, right;
    bool first = true;
    for (char c:variables) {
        if (first) {
            if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
                throw "illegal variable assignment!";
            first = false;
        } else {
            if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_') || (c == '=') || (c == ';') ||
                  (c >= 48 && c <= 57) || (c == '.')||(c == '-')))
                throw "illegal variable assignment!";
        }
        if (c != '=' && c != ';') {
            s += c;
        } else if (c == '=') {
            left = s;
            s = "";
        } else if (c == ';') {
            for (char e:s) {
                if (!((e >= 48 && e <= 57) || e == '.')) {
                    throw "invalid value";
                }
            }
            right = s;
            s = "";
            if (varMap.count(left)) {
                varMap.at(left) = right;
            } else
                varMap.insert({left, right});
            first = true;
        }
    }
    right = s;
    if (varMap.count(left)) {
        varMap.at(left) = right;
    } else
        varMap.insert({left, right});
}

