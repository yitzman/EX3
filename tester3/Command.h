//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_COMMAND_H
#define MILESTONE1_COMMAND_H

using namespace std;
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <chrono>

class Command {
    virtual int execute() = 0;
};


#endif //MILESTONE1_COMMAND_H
