//
// Created by yitzi on 07/11/2019.
//

#ifndef UNTITLED_PLUS_H
#define UNTITLED_PLUS_H


#include "BinaryOperator.h"

class Plus : public BinaryOperator {
public:

    Plus(Expression *right, Expression *left);

    double calculate() override;

};


#endif //UNTITLED_PLUS_H
