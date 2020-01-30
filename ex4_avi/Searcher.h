//
// Created by avi on 13/01/2020.
//

#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H
using namespace std;

#include "Searcheable.h"
#include <queue>
#include <unordered_map>
template <typename T>
class Searcher {
public:
    virtual State<T> search(Searcheable<T>& searcheable) = 0;
    virtual Searcher<T>* clone() = 0;
    virtual ~Searcher(){};
};


#endif //MILESTONE2_SEARCHER_H
