//
// Created by yitzi on 06/11/2019.
//

#include "Variable.h"

Variable::Variable(string n, double val) : value(val), name(n) {
}

void Variable::setName(string n) {
    Variable::name = n;
}

void Variable::setValue(double val) {
    Variable::value = val;
}

double Variable::getValue() const {
    return value;
}

string Variable::getName() const {
    return name;
}

Variable &Variable::operator++() {
    ++this->value;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    --this->value;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double num) {
    this->value += num;
    return *this;
}

Variable::~Variable() {

}

Variable &Variable::operator-=(double num) {
    this->value -= num;
    return *this;
}

double Variable::calculate() {
    return this->value;
}

