#include <iostream>
#include "Tools.h"
#include "Commands/Initialize.h"
#include "Logger.h"
#include "Commands/NewChange.h"

using namespace std;

Tools *Tools::p_instance = 0;
Logger *Logger::p_instance = 0;

int main()
{
    Tools* tools = Tools::getInstance();
    Logger* logger = Logger::getInstance();
    Initialize init;
    NewChange newChange;
    cout<<"Create"<<" "<<init.CreateFolder()<<endl;
    cout<<"Dirs"<<" "<<init.CreateSubDirs();
    cout<<endl<<"Files"<<" "<<init.CreateFiles();
    cout<<newChange.CreateDirsWithHashTitle();
//    tools.ReadAllFiles();

}