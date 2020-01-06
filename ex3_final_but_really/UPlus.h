//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_UPLUS_H
#define UNTITLED_UPLUS_H


#include "UnaryOperator.h"

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *expession);

    double calculate() override;

    virtual ~UPlus();

};


#endif //UNTITLED_UPLUS_H
