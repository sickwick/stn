//
// Created by Mikel Shcherbakov on 18.10.2019.
//

#ifndef STN_INITIALIZE_H
#define STN_INITIALIZE_H

#include <filesystem>
#include <string>

class Initialize{
private:
    string path = Tools::getInstance()->path + "/.stn";
public:

    bool CreateFolder(){
        int dir = filesystem::create_directory(this->path);
        if(!dir){
            return false;
        }

        return true;
    }

};

#endif //STN_INITIALIZE_H
