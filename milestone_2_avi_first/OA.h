//
// Created by avi on 19/01/2020.
//

#ifndef MILESTONE2_OA_H
#define MILESTONE2_OA_H

#include "Solver.h"
#include "Searcher.h"
#include "Astar.h"
#include "BfsSearch.h"
#include "Dfs.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include "State.h"
#include "Matrix.h"
#include "BestFirstSearch.h"

class OA : public Solver<vector<string>, string>{
public:
    string solve(vector<string> prob);
    vector<vector<int>> createMatrixOfInt(vector<string> vec);
    vector<vector<State<string>>>& createMatrixOfStates(vector<vector<int>> matrix_int, int x_goal, int y_goal);
    unordered_map<string, vector<State<string>*>*> createMap(vector<vector<State<string>>>& matrix_state);
    string createSolution(State<string> s, string start_pos);
};







#endif //MILESTONE2_OA_H
