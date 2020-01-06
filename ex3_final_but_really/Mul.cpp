//
// Created by yitzi on 06/11/2019.
//

#include "Mul.h"

double Mul::calculate() {
    return left->calculate()*right->calculate();
}

Mul::Mul(Expression *one, Expression *two) : BinaryOperator(one, two) {}

Mul::~Mul() {

}
