//
// Created by yitzi on 07/11/2019.
//

#ifndef UNTITLED_UNARYOPERATOR_H
#define UNTITLED_UNARYOPERATOR_H

#include "Expression.h"


//#include "Expression.h"
class UnaryOperator : public Expression {
public:
    virtual ~UnaryOperator();

protected:
    Expression *expression;
};


#endif //UNTITLED_UNARYOPERATOR_H
