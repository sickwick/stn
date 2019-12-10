#include <iostream>
#include <string>
#include "Tools.h"
#include "Logger.h"
#include "Controller.h"

using namespace std;

Tools *Tools::p_instance = 0;
Logger *Logger::p_instance = 0;

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
    return 0;
}