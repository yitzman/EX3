//
// Created by avi on 17/12/2019.
//

#include <cstring>
#include "OpenServerCommand.h"
std::mutex mtx;

//constructor
OpenServerCommand::OpenServerCommand(double port) : m_port(port) {}

int OpenServerCommand::execute() {

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr<<"could not create a socket"<<endl;
        return -1;
    }
    //bind socket to IP address
    //we first create the sockaddr obj.
    sockaddr_in address;//in means IP4
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = inet_addr("127.0.0.1");//give me any IP allocated for my machine.
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(m_port);
    //we need to convert our number
    //to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr<<"could not bind socket to an IP"<<endl;
        return -1;
    }

    if (listen(socketfd, 1) == -1) {
        cerr<<"Error during listening command"<<endl;
    }
    int addrlen = sizeof(address);
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t*)&addrlen);

    if (client_socket == -1) {
        cerr<<"Error accepting"<<endl;
        return -1;
    }
    m_fd = client_socket;

    return 1;
}

double OpenServerCommand::getInfoAboutSim(string var) {
    mtx.lock();
    double val = m_map[var];
    mtx.unlock();
    return val;
}

/*
 * reading a line of 36 values seprated by comma from the simulater every 10 secondes.
 * this method should run as long as there is a connection.
 */
int OpenServerCommand::readingInfoFromSim() {
    int valread = 1;
    while(valread != 0) {
        mtx.lock();
        char buffer[100000] = {0};
        valread = read(m_fd, buffer, 10000);
        insertingBufferToMap(buffer, strlen(buffer));
        mtx.unlock();
    }
    return 0;
}

/*
 * @param the line from the simulater of 36 values seprated with comma.
 *
 * the method puts all the values in m_array_vals in order.
 * then transfer it to unordered_map according to the order
 * specified in the generic_small.xml.
 */
int OpenServerCommand::insertingBufferToMap(char *buffer, int buffer_len) {
    int array_index = 0;
    //stores a singel value from the line.
    string val = "";
    //going over the line
    for (int i; i < buffer_len; i++) {
        if (buffer[i] == ',') {
            m_array_vals[array_index] = atof(val.c_str());
            val = "";
            array_index++;
            continue;
        }
        val = val + buffer[i];
    }
    //loading to map.
    m_map["/instrumentation/airspeed-indicator/indicated-speed-kt"] = m_array_vals[0];
    m_map["/sim/time/warp"] = m_array_vals[1];
    m_map["/controls/switches/magnetos"] = m_array_vals[2];
    m_map["/instrumentation/heading-indicator/offset-deg"] = m_array_vals[3];
    m_map["/instrumentation/altimeter/indicated-altitude-ft"] = m_array_vals[4];
    m_map["/instrumentation/altimeter/pressure-alt-ft"] = m_array_vals[5];
    m_map["/instrumentation/attitude-indicator/indicated-pitch-deg"] = m_array_vals[6];
    m_map["/instrumentation/attitude-indicator/indicated-roll-deg"] = m_array_vals[7];
    m_map["/instrumentation/attitude-indicator/internal-pitch-deg"] = m_array_vals[8];;
    m_map["/instrumentation/attitude-indicator/internal-roll-deg"] = m_array_vals[9];;
    m_map["/instrumentation/encoder/indicated-altitude-ft"] = m_array_vals[10];;
    m_map["/instrumentation/encoder/pressure-alt-ft"] = m_array_vals[11];;
    m_map["/instrumentation/gps/indicated-altitude-ft"] = m_array_vals[12];;
    m_map["/instrumentation/gps/indicated-ground-speed-kt"] = m_array_vals[13];;
    m_map["/instrumentation/gps/indicated-vertical-speed"] = m_array_vals[14];
    m_map["/instrumentation/heading-indicator/indicated-heading-deg"] = m_array_vals[15];;
    m_map["/instrumentation/magnetic-compass/indicated-heading-deg"] = m_array_vals[16];;
    m_map["/instrumentation/slip-skid-ball/indicated-slip-skid"] = m_array_vals[17];
    m_map["/instrumentation/turn-indicator/indicated-turn-rate"] = m_array_vals[18];
    m_map["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = m_array_vals[19];
    m_map["/controls/flight/aileron"] = m_array_vals[20];
    m_map["/controls/flight/elevator"] = m_array_vals[21];
    m_map["/controls/flight/rudder"] = m_array_vals[22];
    m_map["/controls/flight/flaps"] = m_array_vals[23];
    m_map["/controls/engines/engine/throttle"] = m_array_vals[24];
    m_map["/controls/engines/current-engine/throttle"] = m_array_vals[25];
    m_map["/controls/switches/master-avionics"] = m_array_vals[26];
    m_map["/controls/switches/starter"] = m_array_vals[27];
    m_map["/engines/active-engine/auto-start"] = m_array_vals[28];
    m_map["/controls/flight/speedbrake"] = m_array_vals[29];
    m_map["/sim/model/c172p/brake-parking"] = m_array_vals[30];
    m_map["/controls/engines/engine/primer"] = m_array_vals[31];
    m_map["/controls/engines/current-engine/mixture"] = m_array_vals[32];
    m_map["/controls/switches/master-bat"] = m_array_vals[33];
    m_map["/controls/switches/master-alt"] = m_array_vals[34];
    m_map["/engines/engine/rpm"] = m_array_vals[35];

    return 0;
}


