//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_MUL_H
#define UNTITLED_MUL_H


#include "BinaryOperator.h"

class Mul: public BinaryOperator {
public:
    Mul(Expression *right, Expression *left);

    double calculate() override;

    virtual ~Mul();

};


#endif //UNTITLED_MUL_H
