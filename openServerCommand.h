//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H

#include "Command.h"

class openServerCommand : public Command{
    void execute() override ;
    void execute(string s) override;
    void execute(string s1, string s2) override;
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
