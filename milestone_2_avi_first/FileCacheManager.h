//
// Created by avi on 15/01/2020.
//

#ifndef MILESTONE2_FILECACHEMANAGER_H
#define MILESTONE2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <string>
#include <unordered_map>
using namespace std;
template <typename P, typename S>
class FileCacheManager : public CacheManager<P, S>{
private:
    unordered_map<P, S> m_map;
public:
    bool isThereSolution( P prob);
    int writeSolution(S sol, P prob);
    S getSolution(P prob);
};

template<typename P, typename S>
bool FileCacheManager<P, S>::isThereSolution(P prob) {
    return !(m_map.find(prob) == m_map.end());
}

template<typename P, typename S>
int FileCacheManager<P, S>::writeSolution(S sol, P prob) {
    m_map[prob] = sol;
}

template<typename P, typename S>
S FileCacheManager<P, S>::getSolution(P prob) {
    return m_map[prob];
}


#endif //MILESTONE2_FILECACHEMANAGER_H
