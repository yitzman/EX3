//
// Created by yitzi on 06/11/2019.
//

#include "UMinus.h"

double UMinus::calculate() {
    return -expression->calculate();
}

UMinus::UMinus(Expression *expr) {
    this->expression = expr;
}

UMinus::~UMinus() {

}
