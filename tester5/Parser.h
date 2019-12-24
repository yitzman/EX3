//
// Created by avi on 21/12/2019.
//

#ifndef MILESTONE1_PARSER_H
#define MILESTONE1_PARSER_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>
#include <unordered_map>
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include "DefineVarCommend.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "Lexer.h"
#include "Interpreter/Expression.h"
#include "Interpreter/Interpreter.h"

using namespace std;

class Parser {
private:
    vector<vector<string>> m_vector;
    bool m_server_established = false;
    bool m_client_established = false;
    unordered_map<string, DefineVarCommend*> m_map_var;
    ConnectCommand* m_connect_command = nullptr;
    OpenServerCommand* m_open_command = nullptr;
    vector<std::thread*> m_thread_vector;
    vector<string> m_var_name_vector;

public:
    explicit Parser(vector<vector<string>> v);
    int execute();

    int parserConnect(vector<string> line);
    int parserOpenServer(vector<string> line);
    int parserDefineVarLeft(vector<string> line);
    int parserDefineVarRight(vector<string> line);
    int parserDefineVarEqual(vector<string> line);
    int parserSetNewVal(vector<string> line);
    int parserSleep(vector<string> line);
    int parserPrint(vector<string> line);
    int parserWhile(vector<string> line);
    int parserFunc(vector<string> line);
    int parserIf(vector<string> line);
    double parserInterpert(string str);

private:
    vector<string> cuttingArgumentsInConnect(string line);
    vector<string> getVariables(string line);
};


#endif //MILESTONE1_PARSER_H
