#include <iostream>
#include <unordered_map>
#include "Matrix.h"
#include "BfsSearch.h"
#include "Dfs.h"
#include "Astar.h"
#include <string>
#include "MyClientHandler.h"
using namespace std;
int main() {
    MyClientHandler ch;
    cout<<ch.handleClient(5, 5)<<endl;
    return 0;
}
/*
unordered_map<string, vector<State<string>>> map;
unordered_map<string, pair<int, int>> map_index;
vector<vector<State<string>>> matrix;
vector<vector<State<string>>> matrix2;
vector<State<string>> vec_name;
int size = 10;
int m1[10][10] = {0};
for (int i = 0; i < size; ++i) {
vector<State<string>> v;
for (int j = 0; j < size; ++j) {

if (i == 9 && j == 8) {
string str = to_string(i) + "," + to_string(j);
State<string> s(str, 2, nullptr);
vec_name.push_back(s);
v.push_back(s);
m1[i][j] = 2;
cout<<2;
cout<<",";
pair<int, int> p(i, j);
map_index[str] = p;
continue;
}

string str = to_string(i) + "," + to_string(j);
State<string> s(str, i + j, nullptr);
s.setH(abs(j-9) + abs(i-9));
vec_name.push_back(s);
v.push_back(s);
m1[i][j] = i + j;
cout<<i + j;
cout<<",";
pair<int, int> p(i, j);
map_index[str] = p;
}
cout<<endl;
matrix.push_back(v);
}
//Matrix<string> matrix1;


for (int i = 0; i < size; ++i) {
for (int j = 0; j < size; ++j) {
vector<State<string>> v;
if (i != 0) {
v.push_back(matrix[i-1][j]);
}
if (j != 0) {
v.push_back(matrix[i][j - 1]);
}
if (i < size - 1) {
v.push_back(matrix[i + 1][j]);
}
if (j < size - 1) {
v.push_back(matrix[i][j + 1]);
}
matrix2.push_back(v);
map[matrix[i][j].getState()] = v;
}
}
if (map.find(matrix[0][0].getState()) == map.end()) {
cout<<"prob"<<endl;
} else {
cout<<map["9,9"][1].getState()<<endl;
}


Matrix<string> matrix1(map, matrix[0][0], matrix[9][9], map_index);
Searcheable<string>* searcheable = &matrix1;
BfsSearch<string> bfs;
Dfs<string> dfs;
Astar<string> astar;
//State<string> state_bfs = bfs.search(matrix1);
//State<string> state_dfs = dfs.search(matrix1);
State<string> state_astar = astar.search(matrix1);

std::cout << "Hello, World!" << std::endl;
*/