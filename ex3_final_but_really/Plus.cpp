//
// Created by yitzi on 07/11/2019.
//

#include "Plus.h"

double Plus::calculate() {
    return right->calculate()+left->calculate();

}

Plus::Plus(Expression *one, Expression *two) : BinaryOperator(one, two) {}
