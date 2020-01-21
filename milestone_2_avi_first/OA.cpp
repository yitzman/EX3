//
// Created by avi on 19/01/2020.
//
#include "OA.h"
string OA::solve(vector<string> vec_string) {
    int num_row = vec_string.size();
    string start_pos = vec_string[num_row - 2];
    string str_goal_x (vec_string[num_row - 1], 0, vec_string[num_row - 1].find(","));
    string str_goal_y (vec_string[num_row - 1], vec_string[num_row - 1].find(",") + 1, vec_string[num_row - 1].size() - 1);
    string str_start_x (vec_string[num_row - 2], 0, vec_string[num_row - 2].find(","));
    string str_start_y (vec_string[num_row - 2], vec_string[num_row - 2].find(",") + 1, vec_string[num_row - 2].size() - 1);

    pair<int, int> p_goal = make_pair(stoi(str_goal_x), stoi(str_goal_y));
    pair<int, int> p_start = make_pair(stoi(str_start_x), stoi(str_start_y));

    vec_string.resize(num_row - 2);
    vector<vector<int>> v_int  = createMatrixOfInt(vec_string);
    vector<vector<State<string>>> matrix_states = createMatrixOfStates(v_int, p_goal.first, p_goal.second);
    unordered_map<string, vector<State<string>*>*> map = createMap(matrix_states);

    State<string> goal_state = matrix_states[p_goal.first][p_goal.second];
    State<string> start_state = matrix_states[p_start.first][p_start.second];

    Matrix<string> matrix_obj(map, matrix_states[p_start.first][p_start.second], matrix_states[p_goal.first][p_goal.second]);
    Searcheable<string>* searcheable = &matrix_obj;

    //Astar<string> astar;
    //State<string> s_astar = astar.search(*searcheable);

    //string sol = createSolution(s_astar, start_pos);

    //BfsSearch<string> bfs;
    //State<string> s_bfs = bfs.search(*searcheable);

    //string sol = createSolution(s_bfs, start_pos);

    //Dfs<string> dfs;
    //State<string> s_dfs = dfs.search(*searcheable);

    //string sol = createSolution(s_dfs, start_pos);

    BestFirstSearch<string> bestfs;
    State<string> s_bestfs = bestfs.search(*searcheable);

    string sol = createSolution(s_bestfs, start_pos);

    return sol;

}

vector<vector<int>> OA::createMatrixOfInt(vector<string> vec) {
    vector<vector<int>> v;

    for (string line : vec) {
        string num = "";
        vector<int> vec_int;
        std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        for (char letter : line) {
            if (letter == ',') {
                vec_int.push_back(stoi(num));
                num = "";
                continue;
            }
            num = num + letter;
        }
        vec_int.push_back(stoi(num));
        v.push_back(vec_int);
    }

    return v;
}

vector<vector<State<string>>>& OA::createMatrixOfStates(vector<vector<int>> matrix_int, int x_goal, int y_goal) {

    vector<vector<State<string>>>* matrix_state = new vector<vector<State<string>>>;
    int col_size = matrix_int[0].size();
    int row_size = matrix_int.size();

    for (int row = 0; row < row_size; ++row) {
        vector<State<string>>* v_states = new vector<State<string>>;
        for (int col = 0; col < col_size; ++col) {
            string str = to_string(row) + "," + to_string(col);
            State<string> s(str, matrix_int[row][col], nullptr);
            //s.setH(abs(col - x_goal) + abs(row - y_goal));
            (*v_states).push_back(s);
            cout<<matrix_int[row][col];
            cout<<",";
        }

        (*matrix_state).push_back(*v_states);
        cout<<endl;
    }

    return *matrix_state;
}

unordered_map<string, vector<State<string>*>*> OA::createMap(vector<vector<State<string>>>& matrix_state) {
    unordered_map<string, vector<State<string>*>*> map;
    int col_size = matrix_state[0].size();
    int row_size = matrix_state.size();
    for (int i = 0; i < row_size; ++i) {
        for (int j = 0; j < col_size; ++j) {

            vector<State<string>*>* v = new vector<State<string>*>;
            //vector<State<string>> v = *v_temp;
            if (i != 0 && matrix_state[i-1][j].getCost() >= 0) {
                (*v).push_back(&matrix_state[i-1][j]);
            }
            if (j != 0 && matrix_state[i][j-1].getCost() >= 0) {
                (*v).push_back(&matrix_state[i][j - 1]);
            }
            if (i < row_size - 1 && matrix_state[i+1][j].getCost() >= 0) {
                (*v).push_back(&matrix_state[i + 1][j]);
            }
            if (j < col_size - 1 && matrix_state[i][j+1].getCost() >= 0) {
                (*v).push_back(&matrix_state[i][j + 1]);
            }
            map[matrix_state[i][j].getState()] = v;
        }
    }

    //cout<<"Sd";
    return map;
}

string OA::createSolution(State<string> s, string start_pos) {
    string sol = "";
    State<string> temp = s;
    string state = s.getState();
    vector<State<string>> v_states;
    int num_states = 0;
    while (s.getState() != start_pos) {
        num_states++;
        v_states.push_back(s);
        s = s.getFather();
    }
    v_states.push_back(s);
    bool first_time = true;
    for (int i = num_states; i > 0; --i) {
        string curr_state = v_states[i].getState();
        string str_curr_x (curr_state, 0, curr_state.find(","));
        string str_curr_y (curr_state, curr_state.find(",") + 1, curr_state.size() - 1);

        pair<int, int> p_curr = make_pair(stoi(str_curr_x), stoi(str_curr_y));

        State<string> child = v_states[i - 1];
        string child_state = child.getState();
        string str_child_x (child_state, 0, child_state.find(","));
        string str_child_y (child_state, child_state.find(",") + 1, child_state.size() - 1);

        pair<int, int> p_child = make_pair(stoi(str_child_x), stoi(str_child_y));

        if (!first_time) {
            sol = sol + " ,";
        } else {
            first_time = false;
        }

        //row
        if (p_child.first > p_curr.first) {
            sol = sol + "Down (" + to_string(int(v_states[i - 1].getDistance() + v_states[num_states].getCost())) + ")";
        } else if (p_child.first < p_curr.first) {
            sol = sol + "Up (" + to_string(int(v_states[i - 1].getDistance() + v_states[num_states].getCost())) + ")";
        //col
        } else if (p_child.second > p_curr.second) {
            sol = sol + "Right (" + to_string(int(v_states[i - 1].getDistance() + v_states[num_states].getCost())) + ")";
        } else if (p_child.second < p_curr.second) {
            sol = sol + "Left (" + to_string(int(v_states[i - 1].getDistance() + v_states[num_states].getCost())) + ")";
        }
    }

    return sol;
}

