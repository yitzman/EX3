//
// Created by yitzi on 07/11/2019.
//

#include "Minus.h"

double Minus::calculate() {
    return left->calculate()-right->calculate();
}

Minus::Minus(Expression *one, Expression *two) : BinaryOperator(one, two) {}

Minus::~Minus() {

}
