//
// Created by avi on 19/01/2020.
//

#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

template <typename P, typename S>
class Solver {
public:
    virtual S solve(P prob) = 0;
};


#endif //MILESTONE2_SOLVER_H
