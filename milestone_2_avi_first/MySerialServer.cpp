//
// Created by user on 2020-01-13.
//
using namespace std;

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "MySerialServer.h"

using namespace server_side;


bool connected = true;

int MySerialServer::open(int port, ClientHandler *ch) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "could not create a socket" << endl;
        return 1;
    }
    //bind socket to IP address
    //we first create the sockaddr obj.
    sockaddr_in address;//in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//give me any IP allocated for my machine.
    //address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    //we need to convert our number
    //to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "could not bind socket to an IP" << endl;
        return 2;
    }
    //mark socket for lisetning
    if (listen(socketfd, 1) == -1) {
        cerr << "Error during listening command" << endl;
        return 3;
    } else {
        std::cout << "Server is listening" << std::endl;
    }
        int client_socket;
        int result;
        // accepts clients
        while (connected) {
            fd_set rfds;
            FD_ZERO(&rfds);
            FD_SET(socketfd, &rfds);
            struct timeval timer;
            timer.tv_sec = (long) 120;
            timer.tv_usec = 0;
            result = select(socketfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &timer);
            if (result > 0) {
                socklen_t addrlen = sizeof(sockaddr_in);
                client_socket = accept(socketfd, (struct sockaddr *) &address, &addrlen);
            } else {
                connected = false;
                continue;
            }
            if (client_socket == -1) {
                cerr << "Error Accepting" << endl;
                return -4;
            }
            ch->handleClient(client_socket);
            // close client socket
            close(client_socket);
        }
        // close server socket
        close(socketfd);
        return 0;
}
    void MySerialServer::close(int port) {
        connected = false;
    }
