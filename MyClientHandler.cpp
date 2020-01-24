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
#include <mutex>

mutex mtx;
int MyClientHandler::handleClient(int input) {

    //std::unique_lock<std::mutex> lck (mtx);
    vector<string> vec_string;
    char buffer[100000];
    bzero(buffer, 100000);
    bool loop = false;
    int val = 1;
    int num_reads = 0;
    //string s;
    while(!loop) {
        num_reads++;
        bzero(buffer, 100000);
        val = read(input, buffer, 100000);
        string t(buffer);
        int place = t.find("\n");
        string s(t, 0, place);

        cout<<s<<endl;
        //s = buffer;
        if (s.find("end") != std::string::npos) {
            cout<<num_reads<<endl;
            break;
        }
        vec_string.push_back(s);
        //cout<<input<<endl;

    }
    cout<<"before OA"<<endl;

    OA oa;
    string sol = oa.solve(vec_string);
    cout<<sol<<endl;

    send(input, sol.c_str(), sol.size(), 0);
    cout<<endl;
    cout<<sol<<endl;



    return 0;
}
/*
    string line;
    ifstream myfile ("Matrix2.txt");
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
     */
