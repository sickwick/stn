//
// Created by Mikel Shcherbakov on 13.10.2019.
//

#ifndef STN_NEWCHANGE_H
#define STN_NEWCHANGE_H

#include <vector>
#include <string>

class NewChange {
private:
    string *command;
    vector<string> *files;
    string path = Tools::getInstance()->path + "/.stn";

public:
    NewChange() {
        command = new string;
        files = new vector<string>{"main.cpp", "Logger.h"};
    }

private:
//    bool CheckLine(string operation, string arg){
//        if(operation == "add"){
//
//        }
//    }
//    void CheckFiles(){
//
//    }
//
//    bool SearchFileFromDir(string fileName) {
//        // TODO найти нормальный способ поиска файлов
//        for (const auto &entry : fs::directory_iterator(Tools::getInstance()->path)) {
//            this->files->push_back(Tools::getInstance()->CutString(entry.path()));
//            if (Tools::getInstance()->CutString(entry.path()) == fileName) {
//                return true;
//            }
//        }
//
//        return false;
//    }

//
public:
    bool CreateDirsWithHashTitle() {
        ifstream dir;
        bool isCreated = true;

        for (int i = 0; i < this->files->size(); i++) {
            filesystem::create_directory(
                    this->path + "/objects/" + to_string(Tools::getInstance()->CreateHash(this->files->at(i))));
        }

        for (int i = 0; i < this->files->size(); i++) {
            dir.open(Tools::getInstance()->path + "/objects/" + this->files->at(i));
            if (!dir.is_open()) {
                Logger::getInstance()->LogError(
                        "Directory " + this->files->at(i) + " didn't create");
                isCreated = false;
            }
        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("Directory created successfully");
        }

        return isCreated;
    }

};


#endif //STN_NEWCHANGE_H
