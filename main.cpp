#include <iostream>
#include <unordered_map>
#include "Matrix.h"
#include "BfsSearch.h"
#include "Dfs.h"
#include "Astar.h"
#include <string>
#include "MyClientHandler.h"
//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <thread>




using namespace std;
int main() {
    bool connected = true;
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;
    int connFd;
    pthread_t threadA[3];
    vector<thread*> vec_thread;


    portNo = atoi("5600");

    if((portNo > 65535) || (portNo < 2000))
    {
        cerr << "Please enter a port number between 2000 - 65535" << endl;
        return 0;
    }

    //create socket
    listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }

    bzero((char*) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        return 0;
    }

    listen(listenFd, 10);

    //len = sizeof(clntAdd);

    int noThread = 0;
    int result;
    while (noThread < 10 && connected)
    {
        socklen_t len = sizeof(clntAdd);
        /*
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(listenFd, &rfds);
        struct timeval timer;
        timer.tv_sec = (long) 12;
        timer.tv_usec = 0;
        result = select(listenFd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &timer);
        if (result > 0) {


            socklen_t addrlen = sizeof(sockaddr_in);
            //client_socket = accept(socketfd, (struct sockaddr *) &address, &addrlen);

            //this is where client connects. svr will hang in this mode until client conn
            connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);
        } else {
            connected = false;
            continue;
        }
*/
        cout << "Listening" << endl;

        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

        if (connFd < 0)
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }

        MyClientHandler* ch = new MyClientHandler();
        thread *t_var_command = new thread(&MyClientHandler::handleClient, ref(ch), connFd);
        vec_thread.push_back(t_var_command);
        noThread++;
    }

    for(int i = 0; i < vec_thread.size(); i++)
    {
        vec_thread[i]->join();
        //pthread_join(threadA[i], NULL);
    }
}
/*
 * MyClientHandler ch;
    cout<<ch.handleClient(5, 5)<<endl;
    return 0;
unordered_map<string, vector<State<string>>> map;
unordered_map<string, pair<int, int>> map_index;
vector<vector<State<string>>> matrix;
vector<vector<State<string>>> matrix2;
vector<State<string>> vec_name;
int size = 10;
int m1[10][10] = {0};
for (int i = 0; i < size; ++i) {
vector<State<string>> v;
for (int j = 0; j < size; ++j) {

if (i == 9 && j == 8) {
string str = to_string(i) + "," + to_string(j);
State<string> s(str, 2, nullptr);
vec_name.push_back(s);
v.push_back(s);
m1[i][j] = 2;
cout<<2;
cout<<",";
pair<int, int> p(i, j);
map_index[str] = p;
continue;
}

string str = to_string(i) + "," + to_string(j);
State<string> s(str, i + j, nullptr);
s.setH(abs(j-9) + abs(i-9));
vec_name.push_back(s);
v.push_back(s);
m1[i][j] = i + j;
cout<<i + j;
cout<<",";
pair<int, int> p(i, j);
map_index[str] = p;
}
cout<<endl;
matrix.push_back(v);
}
//Matrix<string> matrix1;


for (int i = 0; i < size; ++i) {
for (int j = 0; j < size; ++j) {
vector<State<string>> v;
if (i != 0) {
v.push_back(matrix[i-1][j]);
}
if (j != 0) {
v.push_back(matrix[i][j - 1]);
}
if (i < size - 1) {
v.push_back(matrix[i + 1][j]);
}
if (j < size - 1) {
v.push_back(matrix[i][j + 1]);
}
matrix2.push_back(v);
map[matrix[i][j].getState()] = v;
}
}
if (map.find(matrix[0][0].getState()) == map.end()) {
cout<<"prob"<<endl;
} else {
cout<<map["9,9"][1].getState()<<endl;
}


Matrix<string> matrix1(map, matrix[0][0], matrix[9][9], map_index);
Searcheable<string>* searcheable = &matrix1;
BfsSearch<string> bfs;
Dfs<string> dfs;
Astar<string> astar;
//State<string> state_bfs = bfs.search(matrix1);
//State<string> state_dfs = dfs.search(matrix1);
State<string> state_astar = astar.search(matrix1);

std::cout << "Hello, World!" << std::endl;
*/