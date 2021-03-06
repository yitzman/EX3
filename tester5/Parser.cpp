//
// Created by avi on 21/12/2019.
//

#include "Parser.h"

//constructor
Parser::Parser(vector<vector<string>> v) : m_vector(v) {}

int Parser::execute() {

    for (auto v : m_vector) {
        //example: openDataServer(5400).
        //needs to run for the entire run.
        if (v[0] == "openDataServer") {
            try {
                parserOpenServer(v);
            } catch (const char *e) {
                if (m_connect_command != nullptr) {
                    delete (m_connect_command);
                    std::cout << e << std::endl;
                }
                if (m_open_command != nullptr) {
                    delete (m_open_command);
                    std::cout << e << std::endl;
                }
                return -1;
            }
            thread *t_open_command = new thread(&OpenServerCommand::readingInfoFromSim, ref(m_open_command));
            m_thread_vector.push_back(t_open_command);

            continue;
        }

        //example: connectControlClient("127.0.0.1",5400 + 2 + h0).
        if (v[0] == "connectControlClient") {
            try {
                parserConnect(v);
            } catch (const char *e) {
                if (m_connect_command != nullptr) {
                    delete (m_connect_command);
                    std::cout << e << std::endl;
                }
                if (m_open_command != nullptr) {
                    delete (m_open_command);
                    std::cout << e << std::endl;
                }
                return -1;
            }
            continue;
        }

        //example: var airspeed <- sim("/instrumentation/airspeed-indicator/indicated-speed-kt").
        //example: var primer -> sim("/controls/engines/engine/primer").
        //example: var x = 3/h0.
        if (v[0] == "var") {
            if (v[2] == "->") {
                try {
                    parserDefineVarRight(v);
                } catch (const char *e) {
                    if (m_connect_command != nullptr) {
                        delete (m_connect_command);
                        std::cout << e << std::endl;
                    }
                    if (m_open_command != nullptr) {
                        delete (m_open_command);
                        std::cout << e << std::endl;
                    }
                    return -1;
                }

            } else if (v[2] == "<-") {
                try {
                    parserDefineVarLeft(v);
                } catch (const char *e) {
                    if (m_connect_command != nullptr) {
                        delete (m_connect_command);
                        std::cout << e << std::endl;
                    }
                    if (m_open_command != nullptr) {
                        delete (m_open_command);
                        std::cout << e << std::endl;
                    }
                    return -1;
                }
                thread *t_var_command = new thread(&DefineVarCommend::getInfoFromSim, m_map_var[v[1]]);
                m_thread_vector.push_back(t_var_command);

            } else if (v[2] == "=") {
                try {
                    parserDefineVarEqual(v);
                } catch (const char *e) {
                    if (m_connect_command != nullptr) {
                        delete (m_connect_command);
                        std::cout << e << std::endl;
                    }
                    if (m_open_command != nullptr) {
                        delete (m_open_command);
                        std::cout << e << std::endl;
                    }
                    return -1;
                }

            }
            m_var_name_vector.push_back(v[1]);
            continue;
        }

        if (v[0] == "Sleep") {
            parserSleep(v);
            continue;
        }

        if (v[0] == "Print") {
            parserPrint(v);
            continue;
        }

        if (v[0] == "while") {
            //parserWhile(v);
            continue;
        }

        //example: rudder = (h0 - heading)/80
        for (auto name : m_var_name_vector) {
            if (v[0] == name) {
                try {
                    parserSetNewVal(v);
                } catch (const char *e) {
                    if (m_connect_command != nullptr) {
                        delete (m_connect_command);
                        std::cout << e << std::endl;
                    }
                    if (m_open_command != nullptr) {
                        delete (m_open_command);
                        std::cout << e << std::endl;
                    }
                    return -1;
                }
            }
        }
    }
    m_connect_command->closeConnection();
    m_open_command->closeConnection();
    return 0;
}

/*
 * @param an math expression that can have variables.
 *
 * @return the calculated expression.
 */
double Parser::parserInterpert(string str) {
    vector<string> variables = getVariables(str);
    Interpreter *intrptr = new Interpreter();
    for(string s : variables) {
        intrptr->setVariables(s + "=" + to_string(m_map_var[s]->getValue()));
    }
    Expression *e = intrptr->interpret(str);
    return (e->calculate());
    //return atof(str.c_str());
}

/*example: openDataServer(5400 + 2 - h0).
 *
 * relates to the binding "<-"
 *
 * @param a line that holds the command to open a server
 * and wait for the simulator to connect.
 *
 */
int Parser::parserOpenServer(vector<string> line) {
    //interpets the port expression.
    double port = parserInterpert(line[1]);

    m_open_command = new OpenServerCommand(port);
    if (m_open_command->execute() == -1) {
        throw "could not open a server. append in openDataServer .execute command";
    }
    m_server_established = true;
    return 0;
}


/*example: connectControlClient("127.0.0.1",5400 + 2 + h0).
 *
 * relates to the binding "->".
 *
 * @param a line of string that holds the command to connect
 * to the simulator as a client.
 *
 * the method creates a ConnectCommand object, and gives the pointer
 * of the object to the data member m_connect_command.
 */
int Parser::parserConnect(vector<string> line) {
    //cutting between the ip and the port.
    vector<string> v = cuttingArgumentsInConnect(line[1]);

    string server_ip = v[0];
    //interpets the port expression.
    double port = parserInterpert(v[1]);

    m_connect_command = new ConnectCommand(server_ip, port);
    if (m_connect_command->execute() == -1) {
        throw "could not connect to sim. append in connectControlClient .execute command";
    }
    m_client_established = true;
    return 0;
}

/*example: var airspeed <- sim("/instrumentation/airspeed-indicator/indicated-speed-kt")
 *
 * binding: "<-". relates to OpenServerCommand.
 *
 */
int Parser::parserDefineVarLeft(vector<string> line) {
    //if there is no server thats connected to simulator.
    if (!m_server_established) {
        throw "binding var with <- while simulator not connected as client. sent from var command";
    }

    string name_var = line[1];
    string sim_path(line[4], 2, line[4].size() - 3);
    char bind = line[2][0];

    DefineVarCommend *var = new DefineVarCommend(name_var, sim_path, bind, m_open_command);
    var->execute();

    m_map_var[name_var] = var;

    return 0;
}

/*example: var primer -> sim("/controls/engines/engine/primer")
 *
 * binding: "->". relates to ConnectCommand.
 *
 */
int Parser::parserDefineVarRight(vector<string> line) {
    if (!m_client_established) {
        throw "binding var with ->  while not connected to the simulator as client. sent from var command";
    }

    string name_var = line[1];
    string sim_path(line[4], 2, line[4].size() - 3);
    char bind = line[2][1];

    DefineVarCommend *var = new DefineVarCommend(name_var, sim_path, bind, m_connect_command);
    var->execute();

    m_map_var[name_var] = var;

    return 0;
}

/*example: var x = h0/5
 *
 * binding: "="
 *
 */
int Parser::parserDefineVarEqual(vector<string> line) {
    string name_var = line[1];
    char bind = line[2][0];
    double val = parserInterpert(line[3]);

    DefineVarCommend *var = new DefineVarCommend(name_var, bind);
    var->setNewVal(val);
    if (name_var.find(' ') != string::npos) {
        cout << "found prob" << endl;
    }
    m_map_var[name_var] = var;

    return 0;
}

/*example: rudder = (h0 - heading)/80
 *
 * correct for all types of bindings.
 *
 */
int Parser::parserSetNewVal(vector<string> line) {
    string name_var = line[0];

    //checking that variable exits.
    if (m_map_var.find(name_var) == m_map_var.end()) {
        throw "setting new value to undeclared variable. sent from parserSetNewVal";
    }
    double val = parserInterpert(line[2]);


    DefineVarCommend *var = m_map_var[name_var];
    var->setNewVal(val);

    return 0;
}

int Parser::parserWhile(vector<string> line) {
    return 0;
}

int Parser::parserSleep(vector<string> line) {
    int val = (int) parserInterpert(line[1]);
    std::this_thread::sleep_for(std::chrono::milliseconds(val));
    return 0;
}

int Parser::parserPrint(vector<string> line) {
    if (line[1][0] == '\"') {
        string str(line[1], 1, line[1].size() - 2);
        cout << str << endl;
    } else {
        double val = parserInterpert(line[1]);
        cout << val << endl;
    }

    return 0;
}

vector<string> Parser::cuttingArgumentsInConnect(string line) {
    string str_ip = "";
    string str_port = "";
    bool reading_ip = false;
    bool reading_port = false;
    bool reading_comma = false;
    for (auto s : line) {
        if (!reading_ip && s == '\"') {
            reading_ip = true;
            continue;
        }
        if (reading_ip && s == '\"') {
            reading_ip = false;
            reading_comma = true;
            continue;
        }
        if (reading_ip && s != '\"') {
            str_ip = str_ip + s;
            continue;
        }
        if (reading_comma && s == ',') {
            reading_comma = false;
            reading_port = true;
            continue;
        }
        if (reading_port) {
            str_port = str_port + s;
        }

    }
    vector<string> v;
    v.push_back(str_ip);
    v.push_back(str_port);
    return v;
}
//extracts and returns all variables in expression
vector<string> Parser::getVariables(string exp) {
    vector<string> variables;
    string token = "";
    for (char c: exp) {
        if (c == ' ' || c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c == ')') {
            if(token != "" && token !="\t")
                variables.push_back(token);
            token="";
        } else {
            token += c;
        }
    }
    if(token != "" && token !="\t")
        variables.push_back(token);
    return variables;
}
