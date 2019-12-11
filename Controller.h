//
// Created by Mikel Shcherbakov on 10.12.2019.
//
#include "Commands/Initialize.h"
#include "Commands/NewChange.h"
#include "Commands/NewBranch.h"

#ifndef STN_CONTROLLER_H
#define STN_CONTROLLER_H

template <typename T, typename Y>
class ControllerBase{
protected:
    T *_command;
    Y *_operations;
public:
    ControllerBase() {
        this->_operations = Tools::getInstance()->operations;
    }
    virtual bool FindOperation(string command){
        for(int i=0;i<this->_operations->size();i++){
            if(this->_operations->at(i) == command){
                return true;
            }
        }

        return false;
    }
    virtual void CallAction() = 0;
    virtual ~ControllerBase(){
        delete this->_operations;
        delete this->_command;
    }
};

class Controller: public ControllerBase<string, vector<string>>{
public:
    Controller(string command){
        this->_command = new string(command);
        this->CallAction();
    }

    virtual void CallAction() override{
        if(this->FindOperation(this->_command->data())){
            if(this->_command->data() == this->_operations->at(0)){
                Initialize init;
                cout<<"here";
            }
            else if(this->_command->data() == this->_operations->at(1)){
                if(Tools::getInstance()->SearchFileFromDir(".stn")){
                    NewChangeBuilder *newChange = new NewChangeBuilder();
                    newChange->Build(new NewChange());
                    cout<<"here";
                }

            }
            // TODO: Добавать класс commit
            else if(this->_command->data() == this->_operations->at(2)){
                cout<<"add later";
            }
        }
    }
    ~Controller(){}
};

#endif //STN_CONTROLLER_H
