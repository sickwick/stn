//
// Created by Mikel Shcherbakov on 18.10.2019.
//

#ifndef STN_INITIALIZE_H
#define STN_INITIALIZE_H

#include <filesystem>
#include <string>

class Initialize {
private:
    string path = Tools::getInstance()->path + "/.stn";

    vector<string> *subDirs;
public:

    Initialize() {
        //TODO: Вынести в отдельный файл заполнение вектора
        subDirs = new vector<string>{"objects", "versions", "logs"};
    }

    bool CreateFolder() {
        int dir = filesystem::create_directory(this->path);
        if (!dir) {
            return false;
        }

        return true;
    }

    bool CreateSubDirs() {
        vector<int>* dirs = new vector<int>{};
        bool flag = true;
        for (int i = 0; i < this->subDirs->size(); i++) {
            dirs->push_back( filesystem::create_directory(this->path + "/" + this->subDirs->at(i)));
        }

        for(int i=0;i< dirs->size();i++){
            if(dirs->at(i)){
                continue;
            }
            else{
                flag = false;
            }
        }

        if(flag){
            return true;
        }
        return false;
    }

};

#endif //STN_INITIALIZE_H
