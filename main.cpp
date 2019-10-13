#include <iostream>
#include "Tools.h"

namespace fs = std::filesystem;
using namespace std;

int main()
{
    Tools tools;
    cout<<tools.SearchFileFromDir("main.cpp");
    tools.ReadAllFiles();

}