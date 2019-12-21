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
    double m_value;
    string m_name = "";
    string m_sim_path = "";
    char m_binding_direction;
    ConnectCommand* m_connect_command = nullptr;
    OpenServerCommand* m_server_command = nullptr;

public:
    explicit DefineVarCommend(string name, string sim, char binding_direction, ConnectCommand* cc);
    explicit DefineVarCommend(string name, string sim, char binding_direction, OpenServerCommand* osc);
    explicit DefineVarCommend(string name, char binding_direction);

    int execute() override;
    string getName();
    char getBinding();
    int getInfoFromSim();
    int setNewVal(double newVal);

private:
    //if ->
    int sendValToSim(double val);

};


#endif //MILESTONE1_DEFINEVARCOMMEND_H
