//
// Created by yitzi on 06/11/2019.
//

#ifndef UNTITLED_VARIABLE_H
#define UNTITLED_VARIABLE_H

#include <string>
#include "Expression.h"

class Variable : public Expression {
public:
    double value;
    string name;

    Variable(string name, double value);

    double calculate() override;

    double getValue() const;

    void setName(string name);

    void setValue(double value);

    string getName() const;

    Variable &operator++();

    Variable &operator--();

    Variable &operator++(int);

    Variable &operator--(int);

    Variable &operator-=(double);

    Variable &operator+=(double);

    virtual ~Variable();

};

#endif //UNTITLED_VARIABLE_H
