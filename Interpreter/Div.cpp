//
// Created by yitzi on 06/11/2019.
//

#include <bits/exception.h>
#include "Div.h"

double Div::calculate() {
    if (right->calculate() != 0) {
        return left->calculate() / right->calculate();
    }
    throw "division by zero";
}

Div::Div(Expression *one, Expression *two) : BinaryOperator(one, two) {}

Div::~Div() {

}
