//
// Created by avi on 17/12/2019.
//

#include "OpenServerCommand.h"


void OpenServerCommand::execute() {

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr<<"could not create a socket"<<endl;
        return;
    }
    //bind socket to IP address
    //we first create the sockaddr obj.
    sockaddr_in address;//in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//give me any IP allocated for my machine.
    address.sin_port = htons(m_port);
    //we need to convert our number
    //to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr<<"could not bind socket to an IP"<<endl;
        return;
    }

    if (listen(socketfd, 1) == -1) {
        cerr<<"Error during listening command"<<endl;
    }

    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket == -1) {
        cerr<<"Error accepting"<<endl;
        return;
    }

    int valread = 1;
    while(valread != 0) {
        char buffer[10000] = {0};
        valread = read(client_socket, buffer, 10000);
        cout<<buffer<<endl;
    }


    m_fd = client_socket;

}

OpenServerCommand::OpenServerCommand(string s) {
    m_port = atoi(s.c_str());
}

int OpenServerCommand::getInfoAboutSim(string var) {
    return 0;
}
