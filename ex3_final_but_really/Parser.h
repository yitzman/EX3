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
#include <stack>
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <regex>
#include "DefineVarCommend.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "Lexer.h"
#include "Expression.h"
#include "Interpreter.h"

using namespace std;

class Parser {
private:
    vector<vector<string>> m_vector;
    int m_vector_index = -1;

    unordered_map<string, DefineVarCommend*> m_map_var;
    unordered_map<string, DefineVarCommend*> m_map_var_right;
    unordered_map<string, DefineVarCommend*> m_map_var_left;
    unordered_map<string, DefineVarCommend*> m_map_var_equal;
    unordered_map<string, int> m_map_func;

    vector<string> m_var_name_vector;
    vector<string> m_var_name_vector_right;
    vector<string> m_var_name_vector_left;
    vector<string> m_var_name_vector_equal;

    ConnectCommand* m_connect_command = nullptr;
    OpenServerCommand* m_open_command = nullptr;
    vector<std::thread*> m_thread_vector;

    mutex m_mutex_parser_var_left;
    mutex m_mutex_kill_thread;

    condition_variable m_cv_kill;

    bool m_in_scope = false;
    bool m_kill_thread = false;

    bool m_client_established = false;
    bool m_server_established = false;

public:
    explicit Parser(vector<vector<string>> v);

    explicit Parser(vector<vector<string>> v, unordered_map<string, DefineVarCommend *> map_var,
            unordered_map<string,DefineVarCommend *> map_var_equal,
           unordered_map<string, DefineVarCommend *> map_var_right,
           unordered_map<string, DefineVarCommend *> map_var_left,  unordered_map<string,int > map_func,
           vector<string> var_name_vector,
           vector<string> var_name_vector_right, vector<string> var_name_vector_left,
           vector<string> var_name_vector_equal, ConnectCommand *connect_command, OpenServerCommand *open_command);
    int executeScope();

    int parserConnect(vector<string> line);
    int parserOpenServer(vector<string> line);
    int parserDefineVarLeft(vector<string> line);
    int parserDefineVarRight(vector<string> line);
    int parserDefineVarEqual(vector<string> line);
    void parserUpdateVarLeft();
    int parserSetNewVal(vector<string> line);
    int parserSleep(vector<string> line);
    int parserPrint(vector<string> line);
    int parserWhile(vector<string> line);
    int parserFunc(vector<string> line);
    bool parserIsStatementTrue(string left, string sign, string right);
    int parserIf(vector<string> line);
    int parserExecuteScope();
    double parserInterpert(string str);
    int endThread();
    int jumpFunc(vector<vector<string>> v_func);

private:
    vector<string> cuttingArgumentsInConnect(string line);
};


#endif //MILESTONE1_PARSER_H
