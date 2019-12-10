#include <iostream>
#include <string>
#include "Tools.h"
#include "Logger.h"
#include "Controller.h"



using namespace std;

Tools *Tools::p_instance = nullptr;
Logger *Logger::p_instance = nullptr;

int main()
{
    Tools* tools = Tools::getInstance();
    Logger* logger = Logger::getInstance();
    string name;
    string operation;
    cin>>name>>operation;
    Controller controllerBase(operation);

//    Initialize init;
//    NewChange newChange;
//    cout<<"Create"<<" "<<init.CreateFolder()<<endl;
//    cout<<"Dirs"<<" "<<init.CreateSubDirs();
//    cout<<endl<<"Files"<<" "<<init.CreateFiles()<<endl;
//    NewBranch newBranch;

//    tools.ReadAllFiles();

}