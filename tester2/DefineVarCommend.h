//
// Created by avi on 17/12/2019.
//

#ifndef MILESTONE1_DEFINEVARCOMMEND_H
#define MILESTONE1_DEFINEVARCOMMEND_H

#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"

class DefineVarCommend : public Command {
private:
    string m_name = "";
    double m_value;
    string m_sim_path = "";
    bool m_var_effect_sim = false;
    bool m_sim_effect_var = false;
    char m_binding_direction;
    ConnectCommand* m_connect_command;
    OpenServerCommand* m_server_command;

public:
    explicit DefineVarCommend(string name);

    int execute() override;
    int execute(string sim, char binding_direction, ConnectCommand* cc, OpenServerCommand* osc);
    string getName();
    char getBinding();
    //if <-
    string getInfoFromSim();

    int setNewVal(double newVal);

private:
    //if ->
    int sendValToSim(double val);

};


#endif //MILESTONE1_DEFINEVARCOMMEND_H
