//
// Created by avi on 15/01/2020.
//

#ifndef MILESTONE2_FILECACHEMANAGER_H
#define MILESTONE2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <string>
#include <unordered_map>
#include <sys/stat.h>
#include <vector>

using namespace std;

class FileCacheManager : public CacheManager<vector<string>, string>{
private:

public:
    bool isThereSolution(vector<string> prob) override;
    int writeSolution(string sol, vector<string> prob) override;
    string getSolution(vector<string> prob) override;
    string hashString(vector<string> prob);
    CacheManager<vector<string>, string>* clone() override ;
    bool exists (const std::string& filename);
};


#endif //MILESTONE2_FILECACHEMANAGER_H
