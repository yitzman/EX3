//
// Created by avi on 19/01/2020.
//


#include "MyClientHandler.h"


int MyClientHandler::handleClient(int input) {
    vector<string> vec_string;
    char buffer[100000];
    bzero(buffer, 100000);
    bool loop = false;
    int num_reads = 0;
    string prob = "";
    while(!loop) {
        num_reads++;
        bzero(buffer, 100000);
        read(input, buffer, 100000);
        string t(buffer);

        if (t.find("\n") != string::npos) {
            t.resize(t.find("\n") );
        }

        if (t.find("end") != std::string::npos) {
            break;
        }
        prob = prob + t;
        vec_string.push_back(t);
    }
    vec_string.push_back(prob);

    string sol = "";

    if (m_cache->isThereSolution(vec_string)) {
         sol = m_cache->getSolution(vec_string);
    } else {
        vec_string.resize(vec_string.size() - 1);
        sol = m_solver->solve(vec_string);
        vec_string.push_back(prob);
        m_cache->writeSolution(sol, vec_string);
    }


    send(input, sol.c_str(), sol.size(), 0);
    return 0;
}

MyClientHandler::MyClientHandler(Solver<vector<string>, string> *solver, CacheManager<vector<string>, string>* cache) {
    m_solver = solver;
    m_cache = cache;
}

MyClientHandler::MyClientHandler() {}

ClientHandler *MyClientHandler::clone() {
    return new MyClientHandler(m_solver->clone(), m_cache->clone());
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
