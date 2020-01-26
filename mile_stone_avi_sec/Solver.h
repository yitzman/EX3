//
// Created by avi on 19/01/2020.
//

#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

#include <string>
using namespace std;
template <typename P, typename S>
class Solver {
public:
    virtual S solve(P prob) = 0;
    virtual Solver<P, S>* clone() = 0;
    string m_name_solver = "Solver";
};


#endif //MILESTONE2_SOLVER_H
