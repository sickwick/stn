#include <iostream>
#include "Tools.h"

using namespace std;

int main()
{
    Tools tools;
    cout<<tools.SearchFileFromDir("main.cpp");
    tools.ReadAllFiles();

}