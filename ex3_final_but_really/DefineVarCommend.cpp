//
// Created by avi on 17/12/2019.
//

#include "DefineVarCommend.h"


//constructor for "->"
DefineVarCommend::DefineVarCommend(string name, string sim, char binding_direction, ConnectCommand *cc) {
    m_sim_path = sim;
    m_binding_direction = binding_direction;
    m_connect_command = cc;
    m_name = name;
}

//constructor for "="
DefineVarCommend::DefineVarCommend(string name, char binding_direction) {
    m_binding_direction = binding_direction;
    m_name = name;
}

//constructor for "<-"
DefineVarCommend::DefineVarCommend(string name, string sim, char binding_direction, OpenServerCommand *osc) {
    m_sim_path = sim;
    m_binding_direction = binding_direction;
    m_server_command = osc;
    m_name = name;
}

int DefineVarCommend::execute() {
    return 0;
}

string DefineVarCommend::getName() {
    return m_name;
}

char DefineVarCommend::getBinding() {
    return m_binding_direction;
}

/*
 * a method that updates the value of the variable all the time
 * from the simulater using the connection established in
 * open server command.
 *
 * the method should run only if the binding is <-
 * @return -1 if the binding is incorrect
 * */
int DefineVarCommend::getInfoFromSim() {
    //binding should be <-


    mtx1.lock();
    m_value = m_server_command->getInfoAboutSim(m_sim_path);
    mtx1.unlock();
    return 0;
}

/*
 * a method that updates the simulater on the value of
 * the variable.
 *
 * this method should run only if the binding is ->.
 * @return -1 if the binding is incorrect.
 * */
int DefineVarCommend::sendValToSim(double val) {
    string s = "set " + m_sim_path + " " + to_string(val) + " " +'\r' + '\n';

       // cout<<m_name<<" "<<s<<endl;

    if (m_connect_command->isConnected() && m_is_set_been_called) {
        m_connect_command->sendMassageToServer(s);
    }

    return 0;
}

/*
 * a method to set new value to the variable.
 * can run with all bindings.
 * if the binding is -> then the method also updates the simulater.
 */
int DefineVarCommend::setNewVal(double newVal) {
    mtx1.lock();
    m_value = newVal;
    m_is_set_been_called = true;
    mtx1.unlock();
    if (m_binding_direction == '>') {
        sendValToSim(newVal);
    }

    return 0;
}

double DefineVarCommend::getValue() {
    unique_lock<mutex> lck2(mtx1);

    double val = m_value;

    return val;
}




