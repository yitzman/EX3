//
// Created by avi on 25/01/2020.
//

#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H
#include <iostream>
#include <string>
#include "MyClientHandler.h"
#include <string.h> //strlen
#include <stdlib.h>
#include <unistd.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "FileCacheManager.h"
#include "Server.h"

using namespace std;

class MyParallelServer : public Server {
private:
    bool m_connected = false;
public:
    int open(int port, ClientHandler* ch) override;
    int stop() override ;
    ~MyParallelServer(){};
};


#endif //MILESTONE2_MYPARALLELSERVER_H
