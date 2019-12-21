//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_CONNECTCOMMAND_H
#define MILESTONE1_CONNECTCOMMAND_H

#include "Command.h"
class ConnectCommand : public Command {
private:
    int m_port;
    string m_ip;
    int m_fd;
public:
    ConnectCommand(string server_ip, double server_port);

    int execute() override;
    //returns -1 if could not send
    int sendMassageToServer(string massage);
};


#endif //MILESTONE1_CONNECTCOMMAND_H
