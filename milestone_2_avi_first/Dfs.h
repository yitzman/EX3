//
// Created by avi on 15/01/2020.
//

#ifndef MILESTONE2_DFS_H
#define MILESTONE2_DFS_H

#include "Searcher.h"
#include <stack>
template <typename T>
class Dfs : public Searcher<T>{
private:
    unordered_map<T, string> m_map_color;
    unordered_map<T, int> m_map_distance;
    int m_num_of_nodes_visited = 0;

public:
    State<T> search(Searcheable<T>& searcheable);
};

template<typename T>
State<T> Dfs<T>::search(Searcheable<T> &searcheable) {
    stack<State<T>> s;
    m_map_color[searcheable.getInitialState().getState()] = "g";
    searcheable.getInitialState().setDistance(0);
    s.push(searcheable.getInitialState());
    m_num_of_nodes_visited++;
    while (!s.empty()) {
        State<T> u = s.top();
        s.pop();
        m_map_color[u.getState()] = "b";
        m_num_of_nodes_visited++;
        cout<<s.size()<<",";
        vector<State<T>*>& vec = searcheable.getAllPossiableStates(u);
        for (State<T>*& vt : vec) {
            State<T>& v = *vt;
            if (m_map_color.find(v.getState()) == m_map_color.end()) {
                m_map_color[v.getState()] = "g";
                v.setDistance(u.getDistance() + v.getCost());
                v.setFather(u);
                s.push(v);

            }
            if (searcheable.isGoalState(u)) {
                cout<<endl;
                cout<<m_num_of_nodes_visited<<endl;
                return u;
            }
        }
    }
}


#endif //MILESTONE2_DFS_H
