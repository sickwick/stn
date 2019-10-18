#include <iostream>
#include "Tools.h"
#include "Commands/Initialize.h"
#include "Logger.h"
#include <ctime>

using namespace std;

Tools *Tools::p_instance = 0;
Logger *Logger::p_instance = 0;

int main()
{
    Tools* tools = Tools::getInstance();
    Logger* logger = Logger::getInstance();
    Initialize init;
    cout<<"Create"<<" "<<init.CreateFolder()<<endl;
    cout<<"Dirs"<<" "<<init.CreateSubDirs();
    cout<<endl<<"Files"<<" "<<init.CreateFiles();
    cout<<to_string(clock());
//    tools.ReadAllFiles();

}