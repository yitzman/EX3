//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_UMINUS_H
#define UNTITLED_UMINUS_H


#include "UnaryOperator.h"

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *expression);

    double calculate() override;

    virtual ~UMinus();
};


#endif //UNTITLED_UMINUS_H
