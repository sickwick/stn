//
// Created by Mikel Shcherbakov on 13.10.2019.
//

#ifndef STN_NEWCHANGE_H
#define STN_NEWCHANGE_H

#include <vector>
#include <string>

class NewChange {
private:
    vector<string> *files;
    string path = Tools::getInstance()->path + "/.stn";
    vector<string> *hashNames;

public:
    NewChange() {
        files = new vector<string>{"main.cpp", "Logger.h"};
        hashNames = new vector<string>{};
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

public:
    bool CreateDirsWithHashTitle() {
        ifstream dir;
        bool isCreated = true;

        for (int i = 0; i < this->files->size(); i++) {
            string fileName = to_string(Tools::getInstance()->
                    CreateHash(this->GetFileString(this->files->at(i))));
            this->hashNames->push_back(fileName);
            filesystem::create_directory(this->path + "/objects/" + fileName);
        }

        for (int i = 0; i < this->files->size(); i++) {
            dir.open(this->path + "/objects/" + this->hashNames->at(i));
            if (!dir.is_open()) {
                Logger::getInstance()->LogError(
                        "Directory " + this->files->at(i) + " didn't create");
                isCreated = false;
            } else {
                WriteInIndexFile(this->files->at(i), this->hashNames->at(i));
                ofstream file(this->path + "/objects/" + this->hashNames->at(i) + "/" + this->hashNames->at(i));
                if (!file) {
                    Logger::getInstance()->LogError(
                            "file " + this->files->at(i) + " didn't add in " + this->hashNames->at(i));
                }
                file << this->GetFileString(this->files->at(i));
            }
        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("Directory created successfully");
        }

        return isCreated;
    }

    void WriteInIndexFile(string fileName, string fileHash) {
        ofstream index(this->path + "/Index", ios_base::app);

        index << endl << "add" << " " << fileHash << " " << fileName;

        if (index.is_open()) {
            Logger::getInstance()->LogInformation("New line in Index file - add" + fileHash + " " + fileName);
        } else {
            Logger::getInstance()->LogError("Can't create new line");
        }

        index.close();
    }

    string GetFileString(string fileName) {
        ifstream file(Tools::getInstance()->path + "/" + fileName);
        string allText = "";
        string text = "";
        if (!file.is_open()) {
            for (int i = 0; i < Tools::getInstance()->subDirs->size(); i++) {
                file.open(Tools::getInstance()->path + "/" + Tools::getInstance()->subDirs->at(i) + "/" + fileName);
                if (file.is_open()) {
                    break;
                }
            }
        }

        while (getline(file, text)) {
            allText += text;
        }

        file.close();
        return allText;
    }

    ~NewChange() {
        this->hashNames->clear();
        this->files->clear();
    }

};


#endif //STN_NEWCHANGE_H
