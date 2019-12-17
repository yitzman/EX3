//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_COMMAND_H
#define MILESTONE1_COMMAND_H

using namespace std;
#include <string>
class Command {
    virtual void execute() = 0;
    virtual void execute(string s) = 0;
    virtual void execute(string s1, string s2) = 0;
};


#endif //MILESTONE1_COMMAND_H
