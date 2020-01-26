//
// Created by avi on 19/01/2020.
//

#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H


class ClientHandler {
public:
    virtual int handleClient(int input) = 0;
    virtual ClientHandler* clone() = 0;
};


#endif //MILESTONE2_CLIENTHANDLER_H
