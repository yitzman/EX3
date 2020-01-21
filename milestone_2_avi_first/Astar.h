//
// Created by avi on 15/01/2020.
//

#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "Searcher.h"
using namespace std;

template <typename T>
class Astar : public Searcher<T>{
private:
    unordered_map<T, string> m_map_color;
    int m_num_of_nodes_visited = 0;

public:
    State<T> search(Searcheable<T>& searcheable);
};

template<typename T>
State<T> Astar<T>::search(Searcheable<T> &searcheable) {

    auto compare = [](State<string>& s1, State<string>& s2) -> bool
    {
        return s1 > s2;
    };
    std::priority_queue<State<T>, std::vector<State<T>>, decltype(compare)> q(compare);

    m_map_color[searcheable.getInitialState().getState()] = "g";
    searcheable.getInitialState().setDistance(0);
    q.push(searcheable.getInitialState());
    m_num_of_nodes_visited++;
    while (!q.empty()) {
        State<T> u = q.top();
        q.pop();
        if (m_map_color[u.getState()] == "b") {
            continue;
        }
        m_map_color[u.getState()] = "b";
        m_num_of_nodes_visited++;
        cout<<q.size()<<",";
        vector<State<T>*>& vec = searcheable.getAllPossiableStates(u);
        for (State<T>*& vt : vec) {
            State<T>& v = *vt;

            if (m_map_color.find(v.getState()) == m_map_color.end()|| m_map_color[v.getState()] == "g") {
                m_map_color[v.getState()] = "g";
                if (v.getDistance()  > u.getDistance() + v.getCost()) {
                    v.setDistance(u.getDistance() + v.getCost());
                    v.setFather(u);
                    q.push(v);
                }
           }
            if (searcheable.isGoalState(u)) {
                cout<<endl;
                cout<<m_num_of_nodes_visited<<endl;
                return u;
            }
        }

    }
}


#endif //MILESTONE2_ASTAR_H
