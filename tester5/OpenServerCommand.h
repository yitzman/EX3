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
    array<double, 36> m_array_vals;
    unordered_map<string, double > m_map;
    bool m_connected = false;

public:
    OpenServerCommand(double port);

    int execute() override ;
    double getInfoAboutSim(string var);
    int readingInfoFromSim();
    int insertingBufferToMap(char* buffer, int buffer_len);
    bool isConnected();
    void closeConnection();
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
