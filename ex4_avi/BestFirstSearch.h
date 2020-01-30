//
// Created by avi on 21/01/2020.
//

#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H

#include "Matrix.h"
#include "Searcher.h"
template <typename T>
class BestFirstSearch : public Searcher<T> {
private:

    //unordered_map<T, int> m_map_distance;
    //queue<State<T>> q2;

public:
    State<T> search(Searcheable<T>& searcheable);
    Searcher<T>* clone() override;
};

template<typename T>
State<T> BestFirstSearch<T>::search(Searcheable<T> &searcheable) {
    unordered_map<T, string> m_map_color;
    int m_num_of_nodes_visited = 0;

    auto compare = [](State<string>& s1, State<string>& s2) -> bool
    {
        return s1 > s2;
    };
    std::priority_queue<State<T>, std::vector<State<T>>, decltype(compare)> q(compare);

    m_map_color[searcheable.getInitialState().getState()] = "g";
    searcheable.getInitialState().setDistance(0);
    q.push(searcheable.getInitialState());
    //m_num_of_nodes_visited++;
    while (!q.empty()) {
        State<T> u = q.top();
        q.pop();
        if (m_map_color[u.getState()] == "b") {
            continue;
        }
        m_map_color[u.getState()] = "b";
        m_num_of_nodes_visited++;
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
                //cout<<endl;
                cout<<m_num_of_nodes_visited<<endl;
                return u;
            }
        }

    }
    return searcheable.getInitialState();
}

template<typename T>
Searcher<T> *BestFirstSearch<T>::clone() {
    return new BestFirstSearch<T>;
}


#endif //MILESTONE2_BESTFIRSTSEARCH_H
