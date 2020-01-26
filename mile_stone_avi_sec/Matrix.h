//
// Created by avi on 13/01/2020.
//

#ifndef MILESTONE2_MATRIX_H
#define MILESTONE2_MATRIX_H

#include "Searcheable.h"
#include <iostream>

template <typename T>
class Matrix : public Searcheable<T>{
private:
    State<T>* m_goal_state;
    State<T>* m_intial_state;
    unordered_map< T, vector<State<T>*>*> m_map;
    unordered_map<T, pair<int, int>> m_map_index;

public:

    explicit Matrix(unordered_map< T, vector<State<T>*>*>& map, State<T>& initia,State<T>& goal);
    State<T>& getInitialState();
    bool isGoalState(State<T> s);
    vector<State<T>*> &getAllPossiableStates(State<T>& s);
    vector<State<T>> getAllNames();
    int getHeuristics(State<T> state);


};
template<typename T>
Matrix<T>::Matrix(unordered_map< T, vector<State<T>*>*>& map, State<T>& initia, State<T>& goal) :m_map(map){
                                                       m_intial_state = &initia;
                                                       m_goal_state = &goal;
                                                   }

template<typename T>
vector <State<T>*> &Matrix<T>::getAllPossiableStates(State<T>& s) {
    return *(m_map[s.getState()]);
}
//9e0
template<typename T>
State<T>& Matrix<T>::getInitialState() {
    return *m_intial_state;
}

template<typename T>
bool Matrix<T>::isGoalState(State<T> s) {
    return *m_goal_state == s;
}

template<typename T>
int Matrix<T>::getHeuristics(State<T> state) {
    /*
    int x = abs(m_map_index[m_goal_state.getState()].first - m_map_index[state.getState()].first);
    int y = abs(m_map_index[m_goal_state.getState()].second - m_map_index[state.getState()].second);
    return x + y;
     */
}


#endif //MILESTONE2_MATRIX_H
