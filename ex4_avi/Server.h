//
// Created by avi on 26/01/2020.
//

#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "ClientHandler.h"
using namespace std;
class Server {
public:
    virtual int open(int port, ClientHandler* ch) = 0;
    virtual int stop() = 0;
    virtual ~Server(){};
};


#endif //MILESTONE2_SERVER_H
