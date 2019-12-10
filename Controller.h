//
// Created by Mikel Shcherbakov on 10.12.2019.
//
#include <string>

#include "Commands/Initialize.h"
#include "Commands/NewChange.h"
#include "Commands/NewBranch.h"

#ifndef STN_CONTROLLER_H
#define STN_CONTROLLER_H

template <typename T, typename Y>
struct Variables{
    T _command;
    Y *_operations;
};

class ControllerBase{
protected:
    Variables<string, vector<string>> *vars = new Variables<string, vector<string>>{};
public:
    ControllerBase() {
        vars->_operations = Tools::getInstance()->operations;
    }
    virtual bool FindOperation(string command){
        for(int i=0;i<this->vars->_operations->size();i++){
            if(this->vars->_operations->at(i) == command){
                return true;
            }
        }

        return false;
    }
    virtual void CallAction(){}
    virtual ~ControllerBase(){
        delete this->vars->_operations;
        delete this->vars;
    }
};

class Controller: public ControllerBase{
public:
    Controller(string command){
        this->vars->_command = command;
        this->CallAction();
    }

    virtual void CallAction() override{
        if(this->FindOperation(this->vars->_command)){
            cout<<"Ik";
        }
    }
    ~Controller() = default;
};

#endif //STN_CONTROLLER_H
