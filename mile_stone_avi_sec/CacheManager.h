//
// Created by avi on 15/01/2020.
//

#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H

template <typename P, typename S>
class CacheManager {
public:
    virtual bool isThereSolution(P prob) = 0;
    virtual int writeSolution(S sol, P prob) = 0;
    virtual S getSolution(P prob) = 0;
    virtual CacheManager<P, S>* clone() = 0;

};


#endif //MILESTONE2_CACHEMANAGER_H
