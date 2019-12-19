//
// Created by avi on 17/12/2019.
//

#include "DefineVarCommend.h"

int DefineVarCommend::execute() {

}

DefineVarCommend::DefineVarCommend(string name) : m_name(name){

}

int DefineVarCommend::execute(string sim, char binding_direction, ConnectCommand* cc, OpenServerCommand* osc) {
    m_sim_path = sim;
    m_binding_direction = binding_direction;
    m_server_command = osc;
    m_connect_command = cc;

    if (cc == nullptr && osc == nullptr) {
        return -1;
    }

    if (m_binding_direction == '<') {
        m_sim_effect_var = true;
        m_var_effect_sim = false;
    } else if (m_binding_direction == '>') {
        m_sim_effect_var = false;
        m_var_effect_sim = true;
    } else {
        return -1;
    }
}

string DefineVarCommend::getName() {
    return m_name;
}

char DefineVarCommend::getBinding() {
    return m_binding_direction;
}

string DefineVarCommend::getInfoFromSim() {
    //binding should be <-
    if (m_binding_direction != '<') {

    }

    return std::__cxx11::string();
}

int DefineVarCommend::sendValToSim(double val) {
    return 0;
}

int DefineVarCommend::setNewVal(double newVal) {
    m_value = newVal;
    if (m_binding_direction == '>') {
        sendValToSim(newVal);
    }
    return 0;
}


