//
// Created by yitzi on 07/11/2019.
//

#ifndef UNTITLED_BINARYOPERATOR_H
#define UNTITLED_BINARYOPERATOR_H


#include "Expression.h"

class BinaryOperator : public Expression {
public:
    BinaryOperator(Expression *, Expression *);

    virtual ~BinaryOperator();

    Expression *right;
    Expression *left;
};


#endif //UNTITLED_BINARYOPERATOR_H
