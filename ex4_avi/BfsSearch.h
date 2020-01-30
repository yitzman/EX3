//
// Created by avi on 13/01/2020.
//

#ifndef MILESTONE2_BFSSEARCH_H
#define MILESTONE2_BFSSEARCH_H

#include "Searcher.h"
template <typename T>
class BfsSearch : public Searcher<T>{
private:

    //unordered_map<T, int> m_map_distance;
    //queue<State<T>> q2;


public:
    State<T> search(Searcheable<T>& searcheable);
    Searcher<T>* clone() override;
};

template<typename T>
State<T> BfsSearch<T>::search(Searcheable<T>& searcheable) {
    unordered_map<T, string> m_map_color;
    int m_num_of_nodes_visited = 0;
    queue<State<T>> q;
    m_map_color[searcheable.getInitialState().getState()] = "g";
    searcheable.getInitialState().setDistance(0);
    q.push(searcheable.getInitialState());
    //m_num_of_nodes_visited++;
    while (!q.empty()) {
        State<T> u = q.front();
        q.pop();
        if (m_map_color[u.getState()] == "b") {
            continue;
        }
        m_map_color[u.getState()] = "b";
        m_num_of_nodes_visited++;
        //cout<<q.size()<<",";
        vector<State<T>*>& vec = searcheable.getAllPossiableStates(u);
        for (State<T>*& vt : vec) {
            State<T>& v = *vt;
            if (m_map_color.find(v.getState()) == m_map_color.end()) {
                m_map_color[v.getState()] = "g";
                v.setDistance(u.getDistance() + v.getCost());
                v.setFather(u);
                q.push(v);
            }
            if (searcheable.isGoalState(u)) {
                //cout<<endl;
                cout<<m_num_of_nodes_visited<<endl;
                return u;
            }
        }
    }

}

template<typename T>
Searcher<T> *BfsSearch<T>::clone() {
    return new BfsSearch<T>;
}


#endif //MILESTONE2_BFSSEARCH_H
