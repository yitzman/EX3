//
// Created by yitzi on 07/11/2019.
//

#ifndef UNTITLED_MINUS_H
#define UNTITLED_MINUS_H


#include "BinaryOperator.h"

class Minus: public BinaryOperator {
    double calculate() override;

public:
    Minus(Expression *, Expression *);

    virtual ~Minus();

};


#endif //UNTITLED_MINUS_H
