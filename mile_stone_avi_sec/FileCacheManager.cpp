//
// Created by avi on 15/01/2020.
//

#include <fstream>
#include "FileCacheManager.h"

bool FileCacheManager::isThereSolution(vector<string> prob) {
    return exists(hashString(prob));
}

int FileCacheManager::writeSolution(string sol, vector<string> prob) {
    fstream fs;
    fs.open(hashString(prob), ios::out );
    fs.write(sol.c_str(), sol.size());
    //fs.write((char*) & sol, sizeof(sol));
    fs.close();
    return 0;
}

string FileCacheManager::getSolution(vector<string> prob) {
    string sol;
    string temp;
    ifstream fs;
    fs.open(hashString(prob));
    //fs.read((sol, );
    while (fs>>temp) {
        sol = sol + temp;
    }
    fs.close();
    return sol;
}

string FileCacheManager::hashString(vector<string> prob) {
    int size_matrix = prob.size();
    string str = prob[prob.size() - 1];
    string total = to_string(size_matrix) + "," + str[0] + ","  + str[str.size()%2]+ "," + str[str.size() - 1]+ ","+to_string(str.size());
    return total;
}

CacheManager<vector<string>, string> *FileCacheManager::clone() {
    new FileCacheManager;
}

bool FileCacheManager::exists(const std::string &filename) {
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}
