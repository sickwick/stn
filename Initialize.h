//
// Created by Mikel Shcherbakov on 18.10.2019.
//

#ifndef STN_INITIALIZE_H
#define STN_INITIALIZE_H

#include <filesystem>
#include <string>
#include <vector>

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
            return false;
        }

        return true;
    }

    bool CreateSubDirs() {
        vector<int> *dirs = new vector<int>{};
        bool isCreated = true;
        for (int i = 0; i < this->subDirs->size(); i++) {
            dirs->push_back(filesystem::create_directory(this->path + "/" + this->subDirs->at(i)));
        }

        for (int i = 0; i < dirs->size(); i++) {
            dirs->at(i) ? isCreated = true : isCreated = false;
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
                isCreated = false;
            }

            file.close();
        }

        return isCreated;
    }

};

#endif //STN_INITIALIZE_H
