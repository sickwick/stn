#include <iostream>
#include <string>
#include "Tools.h"
#include "Logger.h"
#include "Controller.h"

using namespace std;

Logger *Logger::p_instance = 0;
Tools *Tools::p_instance = 0;

int main() {
    Tools *tools = Tools::getInstance();
    Logger *logger = Logger::getInstance();
    string *name = new string();
    string *operation = new string();
    string *argument = new string();
    bool choice = true;
    Controller *controller;
    while (choice) {
        cin >> name->data() >> operation->data() >> argument->data();
        if (string(name->data()) == "ex") {
            choice = false;
        }
        controller = new Controller(operation->data(), argument->data());
    }

    delete name;
    delete operation;
    delete controller;

    return 0;
}