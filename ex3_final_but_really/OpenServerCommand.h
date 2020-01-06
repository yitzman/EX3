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
    std::mutex mtx_open_server;
    condition_variable cv_open_server;
    bool m_reading_from_sim = true;
    bool m_updateing_vars = false;

    OpenServerCommand(double port);

    int execute();
    double getInfoAboutSim(string var);
    int readingInfoFromSim();
    int insertingBufferToMap(char* buffer, int buffer_len);
    bool isConnected();
    void closeConnection();
    bool isReadingFromSim();
    bool isNotReadingFromSim();
};


#endif //MILESTONE1_OPENSERVERCOMMAND_H
