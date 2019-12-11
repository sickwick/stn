#include <iostream>
#include <string>
#include "Tools.h"
#include "Logger.h"
#include "Controller.h"

using namespace std;

Tools *Tools::p_instance = 0;
Logger *Logger::p_instance = 0;

class Base{
public:
    virtual void k(){};
    virtual void s(){};
};

class Child{
public:
    void Create(Base *base){
        base->k();
        base->s();
    }
};

class Parent: public Base{
public:
    virtual void k() override {
        cout<<"OK";
    }
};

class NeParent: public Base{
public:
    virtual void s() override {
        cout<<"IK";
    }
};

int main()
{
    Tools* tools = Tools::getInstance();
    Logger* logger = Logger::getInstance();
    string *name = new string();
    string *operation = new string();
    bool choice = true;
    Controller *controller;
    while(choice){
        cin>>name->data()>>operation->data();
        if(string(name->data()) == "ex"){
            choice = false;
        }
        controller = new Controller(operation->data());
    }
    delete name;
    delete operation;
    delete controller;
//    tools.ReadAllFiles();

//    Child *child = new Child();
//    child->Create(new Parent());
    return 0;
}