//
// Created by avi on 12/01/2020.
//

#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H

#include <vector>
#include <string>
#include <limits>

using namespace std;
template <typename T>
class State {
private:
    T m_state;
    double m_cost;
    int m_h = 0;
    //double m_distance = std::numeric_limits<double>::infinity();
    double m_distance = 100000;
    State<T>* m_father;
    vector<State<T>> m_possiable_next_states;
    string m_name;
    string m_color;
public:
    State(T s, double cost, State<T>* parent);
    T getState();
    double getCost();
    State<T>& getFather();
    vector<State<T>> getNextStates();
    string getName();
    string getColor();
    void setColor(string c);
    void setFather(State<T>& s);
    bool operator==(State<T>& s);
    bool operator<(State<T>& s);
    bool operator>(State<T>& s);
    void setH(int h);
    int getH();
    void setDistance(double d);
    double getDistance();

};
template<typename T>
State<T>::State(T s, double cost, State<T>* parent) : m_state(s), m_cost(cost), m_father(parent){}

template<typename T>
State<T>& State<T>::getFather() {
    return *m_father;
}

template<typename T>
double State<T>::getCost() {
    return m_cost;
}

template<typename T>
T State<T>::getState() {
    return m_state;
}


template<typename T>
void State<T>::setFather(State<T>& s) {
    m_father = new State<T>(s.getState(), s.getCost(), &s.getFather());
    m_father->setH(s.getH());
    m_father->setDistance(s.getDistance());
}

template<typename T>
bool State<T>::operator==(State<T> &s) {
    if (m_state == s.getState()) {
        return true;
    }
    return false;
}

template<typename T>
void State<T>::setH(int h) {
    m_h = h;
}

template<typename T>
int State<T>::getH() {
    return m_h;
}

template<typename T>
double State<T>::getDistance() {
    return m_distance;
}

template<typename T>
void State<T>::setDistance(double d) {
    m_distance = d;
}

template<typename T>
bool State<T>::operator>(State<T> &s) {
    return m_distance + m_h > s.getDistance() + s.getH();
}

template<typename T>
bool State<T>::operator<(State<T> &s) {
    return m_distance + m_h < s.getDistance() + s.getH();
}


#endif //MILESTONE2_STATE_H
