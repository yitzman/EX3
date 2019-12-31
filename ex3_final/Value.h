//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_VALUE_H
#define UNTITLED_VALUE_H

#include "Expression.h"

class Value : public Expression {
public:
    Value(double value);

    double calculate() override;

    virtual ~Value();

private:
    double value;

};


#endif //UNTITLED_VALUE_H
