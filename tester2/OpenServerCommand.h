//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_OPENSERVERCOMMAND_H
#define MILESTONE1_OPENSERVERCOMMAND_H

#include "Command.h"


class OpenServerCommand : public Command{
private:
    int m_port;
    int m_fd;

public:
    OpenServerCommand(string s);

    int execute() override ;
    int getInfoAboutSim(string var);
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
