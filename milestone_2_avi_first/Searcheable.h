//
// Created by avi on 12/01/2020.
//

#ifndef MILESTONE2_SEARCHEABLE_H
#define MILESTONE2_SEARCHEABLE_H
using namespace std;

#include "State.h"
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <chrono>
#include <cstring>
#include <condition_variable>
#include <functional>
#include <vector>
template <typename T>
class Searcheable {
public:
    virtual State<T>& getInitialState() = 0;
    virtual bool isGoalState(State<T> s) = 0;
    virtual vector<State<T>*>& getAllPossiableStates(State<T>& s) = 0;
    virtual int getHeuristics(State<T> state) = 0;

};


#endif //MILESTONE2_SEARCHEABLE_H
