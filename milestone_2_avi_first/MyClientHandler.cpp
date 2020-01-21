//
// Created by avi on 19/01/2020.
//
using namespace std;
#include "MyClientHandler.h"
#include "OA.h"
#include "Matrix.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>


int MyClientHandler::handleClient(int intput, int output) {
    vector<string> vec_string;
    string line;
    ifstream myfile ("matrix_test.txt");
    int num_row = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {

            if (line == "end") {
                break;
            }
            num_row++;
            cout << line << '\n';
            vec_string.push_back(line);
        }
        myfile.close();
    }
    OA oa;
    string sol = oa.solve(vec_string);

    cout<<endl;
    cout<<sol<<endl;
    return 0;
}
