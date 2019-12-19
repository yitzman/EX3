//
// Created by avi on 17/12/2019.
//

#include <cstring>
#include "ConnectCommand.h"

int ConnectCommand::execute() {

    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        cerr<<"could not create a socket"<<endl;
        return -1;
    }

    //we need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(m_ip.c_str()); //the localhost address
    address.sin_port = htons(m_port);
    //we need to convert our number (both port & localhost)
    //to a number that the network understands.

    //Requesting a connection with the server on ip with port
    int is_connect = connect(client_socket, (struct sockaddr*) &address, sizeof(address));
    if(is_connect == -1) {
        cerr<<"could not connect to host server"<<endl;
        return -1;
    } else {
        cout<<"client is now connected to server"<<endl;
    }
    char hello[] = "This was sent from client connectCommand and printed from server command";
    send(client_socket, hello, strlen(hello), 0);
    m_fd = client_socket;
}

ConnectCommand::ConnectCommand(string server_ip, string server_port) : m_port(atoi(server_port.c_str())), m_ip(server_ip) {

}

int ConnectCommand::sendMassageToServer(string massage) {
    massage = "set " + massage;
    send(m_fd, massage.c_str(), strlen(massage.c_str()), 0);
    close(m_fd);
    return 0;
}
