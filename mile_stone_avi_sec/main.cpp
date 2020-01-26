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
#include "MyParallelServer.h"
#include "FileCacheManager.h"
#include "BestFirstSearch.h"
#include "Dfs.h"
#include "BfsSearch.h"
#include "Astar.h"
#include "OA.h"


using namespace std;
int main() {
    MyParallelServer* mps = new MyParallelServer();
    Searcher<string>* searcher = new BestFirstSearch<string>;
    Solver<vector<string>, string>* solver = new OA(searcher);
    CacheManager<vector<string>, string>* cacheManager = new FileCacheManager;
    MyClientHandler* mch = new MyClientHandler(solver, cacheManager);

    mps->open(5600, mch);
}
/*
 *
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

 *
 *
 *
 *
 *
 *
 *
 *
 *
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