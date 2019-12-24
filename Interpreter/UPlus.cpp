//
// Created by yitzi on 06/11/2019.
//

#include "UPlus.h"

UPlus::UPlus(Expression * expession) {
    this->expression=expession;
}

double UPlus::calculate() {
    return expression->calculate();
}

UPlus::~UPlus() {

}
