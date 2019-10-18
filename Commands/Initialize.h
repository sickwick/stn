//
// Created by Mikel Shcherbakov on 18.10.2019.
//

#ifndef STN_INITIALIZE_H
#define STN_INITIALIZE_H

#include <filesystem>
#include <string>
#include <vector>
#include "../Logger.h"

class Initialize {
private:
    string path = Tools::getInstance()->path + "/.stn";

    vector<string> *subDirs;
    vector<string> *files;
public:

    Initialize() {
        //TODO: Вынести в отдельный файл заполнение вектора
        subDirs = new vector<string>{"objects", "versions", "logs"};
        files = new vector<string>{"Index", "objects/info.txt"};
    }

    bool CreateFolder() {
        int dir = filesystem::create_directory(this->path);
        if (!dir) {
            Logger::getInstance()->LogError("Directory didn't create");
            return false;
        }
        Logger::getInstance()->LogInformation("Create main directory");
        return true;
    }

    bool CreateSubDirs() {
        vector<int> *dirs = new vector<int>{};
        bool isCreated = true;
        for (int i = 0; i < this->subDirs->size(); i++) {
            dirs->push_back(filesystem::create_directory(this->path + "/" + this->subDirs->at(i)));
        }

        for (int i = 0; i < dirs->size(); i++) {
            dirs->at(i) ? isCreated = true
                        : isCreated = false, Logger::getInstance()->LogError(
                    "Directory" + to_string(dirs->at(i)) + "didn't create");
        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("Directories created successfully");
        }

        return isCreated;
    }

    bool CreateFiles() {
        ofstream newFile;
        ifstream file;
        bool isCreated = true;

        for (int i = 0; i < this->files->size(); i++) {
            newFile.open(this->path + "/" + this->files->at(i));
            newFile.close();
        }

        for (int i = 0; i < this->files->size(); i++) {
            file.open(this->path + "/" + this->files->at(i));
            if (!file.is_open()) {
                Logger::getInstance()->LogError("File - " + this->files->at(i) + "didn't create");
                isCreated = false;
            }

            file.close();
        }

        if(isCreated){
            Logger::getInstance()->LogInformation("All files created successfully");
        }

        return isCreated;
    }

    ~Initialize() {
        this->files->clear();
        this->subDirs->clear();
    }
};

#endif //STN_INITIALIZE_H
