//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_DIV_H
#define UNTITLED_DIV_H


#include "BinaryOperator.h"

class Div : public BinaryOperator{
public:
    Div(Expression *, Expression *);

    virtual ~Div();

private:
    double calculate() override;

};


#endif //UNTITLED_DIV_H
