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
    string path = string(Tools::getInstance()->path->data()) + "/.stn";

public:
    Initialize() {
        this->CreateFolder();
        this->CreateSubDirs();
        this->CreateFiles();
    }

    bool CreateFolder() {
        int dir = filesystem::create_directory(this->path);
        if (!dir) {
            return false;
        }
        return true;
    }

    bool CreateSubDirs() {
        vector<int> *dirs = new vector<int>{};
        ifstream file;
        bool isCreated = true;
        for (int i = 0; i < Tools::getInstance()->subDirs->size(); i++) {
            dirs->push_back(filesystem::create_directory(this->path + "/" + Tools::getInstance()->subDirs->at(i)));
        }

        for (int i = 0; i < Tools::getInstance()->subDirs->size(); i++) {
            file.open(this->path + "/" + Tools::getInstance()->subDirs->at(i));
            if (!file.is_open()) {
                Logger::getInstance()->LogError(
                        "Directory " + Tools::getInstance()->subDirs->at(i) + " didn't create");
                isCreated = false;
            }
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

        for (int i = 0; i < Tools::getInstance()->fileNames->size(); i++) {
            newFile.open(this->path + "/" + Tools::getInstance()->fileNames->at(i));
            newFile.close();
        }

        for (int i = 0; i < Tools::getInstance()->fileNames->size(); i++) {
            file.open(this->path + "/" + Tools::getInstance()->fileNames->at(i));
            if (!file.is_open()) {
                Logger::getInstance()->LogError("File - " + Tools::getInstance()->fileNames->at(i) + "didn't create");
                isCreated = false;
            }

            file.close();
        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("All files created successfully");
        }

        return isCreated;
    }
};

#endif //STN_INITIALIZE_H
