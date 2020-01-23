//
// Created by user on 2020-01-13.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H


#include "Server.h"

class MySerialServer : public server_side::Server {
public:
    static int open(int port,ClientHandler*);

    static void close(int port);
};

#endif //EX4_MYSERIALSERVER_H
