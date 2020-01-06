//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_CONNECTCOMMAND_H
#define MILESTONE1_CONNECTCOMMAND_H

#include "Command.h"
#include <condition_variable>
#include <cstring>


class ConnectCommand : public Command {
private:
    int m_port;
    string m_ip;
    int m_fd;
    bool m_connected = false;

public:
    ConnectCommand(string server_ip, double server_port);

    int execute();
    //returns -1 if could not send
    int sendMassageToServer(string massage);
    bool isConnected();
    void closeConnection();
};


#endif //MILESTONE1_CONNECTCOMMAND_H
