//
// Created by yitzi on 07/11/2019.
//

#include "BinaryOperator.h"

BinaryOperator::BinaryOperator(Expression *one, Expression *two) : right(two), left(one) {}

BinaryOperator::~BinaryOperator() {

}
