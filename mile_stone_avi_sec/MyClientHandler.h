//
// Created by avi on 19/01/2020.
//

#ifndef MILESTONE2_MYCLIENTHANDLER_H
#define MILESTONE2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "FileCacheManager.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "State.h"
#include "MyClientHandler.h"
#include "OA.h"
#include "Matrix.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <mutex>
#include "Solver.h"
using namespace std;
class MyClientHandler : public ClientHandler {
private:
    Solver<vector<string>, string>* m_solver;
    CacheManager<vector<string>, string>* m_cache;
public:
    MyClientHandler();
    MyClientHandler(Solver<vector<string>, string>* solver, CacheManager<vector<string>, string>* cache);
    int handleClient(int input) override;
    ClientHandler* clone() override;

};


#endif //MILESTONE2_MYCLIENTHANDLER_H
