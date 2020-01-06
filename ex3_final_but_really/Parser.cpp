//
// Created by avi on 21/12/2019.
//

#include "Parser.h"

//constructor
Parser::Parser(vector<vector<string>> v) : m_vector(v) {}

//constructor for running a scope inside a program.
Parser::Parser(vector<vector<string>> v, unordered_map<string, DefineVarCommend *> map_var,
               unordered_map<string, DefineVarCommend *> map_var_equal,
               unordered_map<string, DefineVarCommend *> map_var_right,
               unordered_map<string, DefineVarCommend *> map_var_left, unordered_map<string, int> map_func,
               vector<string> var_name_vector,
               vector<string> var_name_vector_right, vector<string> var_name_vector_left,
               vector<string> var_name_vector_equal, ConnectCommand *connect_command, OpenServerCommand *open_command) :
        m_vector(v), m_map_var(map_var), m_map_var_right(map_var_right),
        m_map_var_left(map_var_left), m_map_var_equal(map_var_equal),
        m_map_func(map_func), m_var_name_vector(var_name_vector), m_var_name_vector_right(var_name_vector_right),
        m_var_name_vector_left(var_name_vector_left), m_var_name_vector_equal(var_name_vector_equal) {
    m_connect_command = connect_command;
    if (connect_command != nullptr) {
        m_client_established = true;
    }
    m_open_command = open_command;
    if (open_command != nullptr) {
        m_server_established = true;
    }
    m_in_scope = true;


}

/*
 * iterating over a scope of code that is in the data memmber m_vector
 * that contains a scope of command lines from a file, where each line is in a diffrent vector<string>,
 * and each token from the line is in a different cell in the vector.
 *
 * the scope can end by either the end of m_vector or '}' which signals the end of the scope.
 *
 * for each line the program checks the first token of the line which tells it what command to execute.
 * for each command that the program identifies it calls the according method that will execute that command.
 *
 * if there is a scope inside a scope the program do a recursion for that scope and then jumps the amount of lines
 * that where executed by the recursion.
 *
 */
int Parser::executeScope() {
    int jump_while = 0;

    if (m_in_scope) {
        thread *t = new thread(&Parser::parserUpdateVarLeft, this);
        m_thread_vector.push_back(t);
    }

    for (auto v : m_vector) {

        m_vector_index++;

        if (jump_while > 0) {
            //cout << v[0] << " in jump_while" << endl;
            jump_while--;
            continue;
        }
        //cout << v[0] << endl;
        //example: openDataServer(5400).
        //needs to run for the entire run.
        if (v[0] == "openDataServer") {
            parserOpenServer(v);
            //creating a thread that is reading vals from simulator.
            thread *t_open_command = new thread(&OpenServerCommand::readingInfoFromSim, ref(m_open_command));
            m_thread_vector.push_back(t_open_command);
            //creating a thread that updates all the variables with '<-' binding from the open_command object.
            thread *t_var_command = new thread(&Parser::parserUpdateVarLeft, this);
            m_thread_vector.push_back(t_var_command);

            continue;
        }

        //example: connectControlClient("127.0.0.1",5400 + 2 + h0).
        if (v[0] == "connectControlClient") {
            parserConnect(v);
            //thread* t_var_command = new thread(&Parser::parserUpdateVarRight, this);
            //m_thread_vector.push_back(t_var_command);

            continue;
        }

        //example: var airspeed <- sim("/instrumentation/airspeed-indicator/indicated-speed-kt").
        //example: var primer -> sim("/controls/engines/engine/primer").
        //example: var x = 3/h0.
        if (v[0] == "var") {
            if (v[2] == "->") {
                parserDefineVarRight(v);

            } else if (v[2] == "<-") {
                parserDefineVarLeft(v);

            } else if (v[2] == "=") {
                parserDefineVarEqual(v);

            }
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

        if (v[0] == "while" || v[0] == "While") {
            jump_while = parserWhile(v);
            continue;
        }

        if (v[0] == "if" || v[0] == "If") {
            jump_while = parserIf(v);
            continue;
        }

        bool v_in_var = false;
        //example: rudder = (h0 - heading)/80
        //checking if the first token is var name.
        for (auto name : m_var_name_vector) {
            if (v[0] == name) {
                parserSetNewVal(v);
                v_in_var = true;
                break;
            }
        }
        if (v_in_var) {
            continue;
        }

        if (v[0] == "}") {
            endThread();
            return m_vector_index;
        }

        //checking if the first token is a function that was declared already.
        //if not it saves the line number in which the scope of the function is at, and the name of the function.
        if (m_map_func.find(v[0]) == m_map_func.end()) {
            m_map_func[v[0]] = m_vector_index + 1;
            vector<vector<string>> _v(m_vector.begin() + m_vector_index + 1, m_vector.end());
            jump_while = jumpFunc(_v);

        } else {
            parserFunc(v);
        }
    }
    endThread();
    m_connect_command->closeConnection();
    m_open_command->closeConnection();
    return 0;
}

/*
 * @param str a math expression that can have variables.
 *
 * @return the calculated expression.
 */
double Parser::parserInterpert(string str) {
    //erasing all spaces in the expression.
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());

    //checking if there is a variable in the scope.
    regex r("(.*)([a-z]+)(.*)");
    smatch m;
    if (!regex_match(str, r)) {
        Interpreter *intrptr = new Interpreter();
        Expression *e = intrptr->interpret(str);
        return (e->calculate());

    }
    Interpreter *intrptr = new Interpreter();
    //creating the string of variable to send setVariables.
    for (string s : m_var_name_vector) {
        intrptr->setVariables(s + "=" + to_string(m_map_var[s]->getValue()));
    }
    Expression *e = intrptr->interpret(str);

    return (e->calculate());
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
    m_open_command->execute();
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
    m_connect_command->execute();
    m_client_established = true;
    return 0;
}

/*example: var airspeed <- sim("/instrumentation/airspeed-indicator/indicated-speed-kt")
 *
 * binding: "<-". relates to OpenServerCommand.
 *
 */
int Parser::parserDefineVarLeft(vector<string> line) {
    string name_var = line[1];
    string sim_path(line[4], 2, line[4].size() - 3);
    char bind = line[2][0];

    DefineVarCommend *var = new DefineVarCommend(name_var, sim_path, bind, m_open_command);
    var->execute();
    //locking because the thread that updates the vars from the simulator is also using this data members.
    unique_lock<mutex> lck(m_mutex_parser_var_left);
    m_map_var[name_var] = var;
    m_map_var_left[name_var] = var;

    m_var_name_vector.push_back(name_var);
    m_var_name_vector_left.push_back(name_var);


    return 0;
}

/*example: var primer -> sim("/controls/engines/engine/primer")
 *
 * binding: "->". relates to ConnectCommand.
 *
 */
int Parser::parserDefineVarRight(vector<string> line) {
    string name_var = line[1];
    string sim_path(line[4], 2, line[4].size() - 3);
    char bind = line[2][1];

    DefineVarCommend *var = new DefineVarCommend(name_var, sim_path, bind, m_connect_command);
    var->execute();

    m_map_var[name_var] = var;
    m_map_var_right[name_var] = var;

    m_var_name_vector.push_back(name_var);
    m_var_name_vector_right.push_back(name_var);

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

    m_map_var[name_var] = var;
    m_map_var_equal[name_var] = var;
    m_var_name_vector.push_back(name_var);
    m_var_name_vector_equal.push_back(name_var);

    return 0;
}

/*example: rudder = (h0 - heading)/80
 *
 * correct for all types of bindings.
 *
 */
int Parser::parserSetNewVal(vector<string> line) {
    string name_var = line[0];
    double val = parserInterpert(line[2]);

    DefineVarCommend *var = m_map_var[name_var];
    var->setNewVal(val);

    return 0;
}

int Parser::parserWhile(vector<string> line) {
    while (parserIsStatementTrue(line[1], line[2], line[3])) {
        parserExecuteScope();
    }

    vector<vector<string>> v(m_vector.begin() + m_vector_index + 1, m_vector.end());
    return jumpFunc(v);
}

int Parser::parserIf(vector<string> line) {
    if (parserIsStatementTrue(line[1], line[2], line[3])) {
        parserExecuteScope();
    }

    vector<vector<string>> v(m_vector.begin() + m_vector_index + 1, m_vector.end());
    return jumpFunc(v);
}

/*
 * @param left the left exp of the if.
 * @param sign the sign of the if.
 * @param right the right exp of the if.
 *
 * @return true if the if statement is true. false otherwise.
 */
bool Parser::parserIsStatementTrue(string left, string sign, string right) {
    double val_left = parserInterpert(left);
    double val_right = parserInterpert(right);
    bool do_if = false;

    if (sign == "!=") {
        do_if = val_left != val_right;
    }
    if (sign == "==") {
        do_if = val_left == val_right;
    }
    if (sign == "<=") {
        do_if = val_left <= val_right;
    }
    if (sign == ">=") {
        do_if = val_left >= val_right;
    }
    if (sign == "<") {
        do_if = val_left < val_right;
    }
    if (sign == ">") {
        do_if = val_left > val_right;
    }

    return do_if;

}

int Parser::parserExecuteScope() {
    vector<vector<string>> v(m_vector.begin() + m_vector_index + 1, m_vector.end());
    endThread();

    Parser p(v, m_map_var, m_map_var_equal, m_map_var_right,
             m_map_var_left, m_map_func,
             m_var_name_vector, m_var_name_vector_right,
             m_var_name_vector_left, m_var_name_vector_equal,
             m_connect_command, m_open_command);
    p.executeScope();

    thread *t = new thread(&Parser::parserUpdateVarLeft, this);
    m_thread_vector.push_back(t);

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


/*
 * ending the thread that updates the variables with left binding.
 */
int Parser::endThread() {
    //makeing sure that the thread is not touching the m_kill_thread data member.
    unique_lock<mutex> lck(m_mutex_kill_thread);
    //this will end the while loop of the thread.
    m_kill_thread = true;
    lck.unlock();
    //waiting for the thread to finish
    (*(m_thread_vector.end() - 1))->join();

    return 0;
}

/*
 * a thread that updates all of the variables with a binding of '<-' from the simultor.
 */
void Parser::parserUpdateVarLeft() {
    //locking to check that the server is not reading values
    std::unique_lock<std::mutex> lck(m_open_command->mtx_open_server);
    m_open_command->cv_open_server.wait(lck, std::bind(&OpenServerCommand::isNotReadingFromSim, m_open_command));

    while (m_open_command->isConnected() && !m_kill_thread) {
        m_mutex_kill_thread.unlock();

        m_mutex_parser_var_left.lock();

        for (auto n : m_var_name_vector_left) {
            m_map_var_left[n]->getInfoFromSim();
        }

        m_mutex_parser_var_left.unlock();
        m_open_command->m_reading_from_sim = true;
        //waiting until the server will update its values from the simulator.
        m_open_command->cv_open_server.wait(lck, std::bind(&OpenServerCommand::isNotReadingFromSim, m_open_command));

        m_mutex_kill_thread.lock();

    }
    if (m_kill_thread) {
        m_mutex_kill_thread.unlock();
    }

}

/*
 * @param line a line that calls a function that was already declared before.
 */
int Parser::parserFunc(vector<string> line) {
    //no var in declarition of the function.
    if (m_vector[m_map_func[line[0]] - 1][1] == "") {

        //the vector that holds the scope to be executed.
        vector<vector<string>> v(m_vector.begin() + m_map_func[line[0]], m_vector.end());
        //ending the thread of updateVarLeft because the funnction will create a thread of its own that will update the vars.
        endThread();

        //creating a parser that will execute the scope of the function using all of the variables from before.
        Parser p(v, m_map_var, m_map_var_equal, m_map_var_right,
                 m_map_var_left, m_map_func,
                 m_var_name_vector, m_var_name_vector_right,
                 m_var_name_vector_left, m_var_name_vector_equal,
                 m_connect_command, m_open_command);

        p.executeScope();

        //recreating the thread that updates the vars with left bindings.
        thread *t = new thread(&Parser::parserUpdateVarLeft, this);
        m_thread_vector.push_back(t);
        return 0;
    }

    double val = parserInterpert(line[1]);
    //getting the string inside the parantessis of the function declaration.
    string s = m_vector[m_map_func[line[0]] - 1][1];
    //getting the name of the var.
    string str(s, s.find("r") + 1, s.size());
    //cleans the spaces.
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());

    DefineVarCommend *var = new DefineVarCommend(str, '=');
    var->setNewVal(val);


    //the vector that holds the scope to be executed.
    vector<vector<string>> v(m_vector.begin() + m_map_func[line[0]], m_vector.end());
    //ending the thread of updateVarLeft because the funnction will create a thread of its own that will update the vars.
    endThread();

    //updateing the data structures that is send to the function scope to be with the vars of the decleration.
    m_map_var[str] = var;
    m_map_var_equal[str] = var;
    m_var_name_vector.push_back(str);
    m_var_name_vector_equal.push_back(str);

    //creating a parser that will execute the scope of the function using all of the variables from before.
    Parser p(v, m_map_var, m_map_var_equal, m_map_var_right,
             m_map_var_left, m_map_func,
             m_var_name_vector, m_var_name_vector_right,
             m_var_name_vector_left, m_var_name_vector_equal,
             m_connect_command, m_open_command);
    //erasing the vars of the function declarition.
    m_map_var.erase(str);
    m_map_var_equal.erase(str);
    m_var_name_vector.erase(m_var_name_vector.end() - 1);
    m_var_name_vector_equal.erase(m_var_name_vector_equal.end() - 1);
    p.executeScope();

    //recreating the thread that updates the vars with left bindings.
    thread *t = new thread(&Parser::parserUpdateVarLeft, this);
    m_thread_vector.push_back(t);
    return 0;

}

/*
 * @param v_func a group of lines. which is a scope of code starting with '{' and ends with '}'.
 *
 * @return the number of line that the scope has.
 *
 * the scope of code can have anouther scope in it so we need to make sure that the number of '{' that we count
 * is equal to the number of '}'.
 * we do that using a stack.
 */
int Parser::jumpFunc(vector<vector<string>> v_func) {
    int jump = 0;
    stack<string> stk;
    //the start of the scope.
    stk.push("{");
    //going over the scope line by line.
    for (auto v : v_func) {
        if (stk.empty()) {
            break;
        }
        jump++;
        if (v[0] == "}") {
            if (stk.top() == "{") {
                stk.pop();
            }
        } else if (v[v.size() - 1] == "{") {
            stk.push("{");
        }
    }
    return jump;
}






