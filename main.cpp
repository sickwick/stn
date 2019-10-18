#include <iostream>
#include "Tools.h"
#include "Initialize.h"

using namespace std;

Tools *Tools::p_instance = 0;

int main()
{
    Tools* tools = Tools::getInstance();
//    tools.ReadAllFiles();

}