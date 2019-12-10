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
    string name;
    string operation;
    cin>>name>>operation;
    Controller controllerBase(operation);


//    tools.ReadAllFiles();
    return 0;
}