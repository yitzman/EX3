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
using namespace std;
class MyClientHandler : public ClientHandler {
public:
    int handleClient(int intput, int output) override;

};


#endif //MILESTONE2_MYCLIENTHANDLER_H
