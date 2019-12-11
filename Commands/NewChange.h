//
// Created by Mikel Shcherbakov on 13.10.2019.
//

#ifndef STN_NEWCHANGE_H
#define STN_NEWCHANGE_H

#include <vector>
#include <string>
#include "NewBranch.h"

template <typename T, typename Y>
class NewChangeBase{
protected:
    Y files;
    Y *hashNames;
    T *path;
public:
    NewChangeBase(): path(this->path = new string(string(Tools::getInstance()->path->data()) + "/.stn")) {}

    virtual void createObjectDirectory(){
        for (int i = 0; i < this->files.size(); i++) {
            string fileName = to_string(Tools::getInstance()->
                    CreateHash(this->GetFileString(this->files.at(i))));
            this->hashNames->push_back(fileName);
            filesystem::create_directory(string(this->path->data()) + "/objects/" + fileName);
        }
    }
    virtual bool CreateDirsWithHashTitle(){}

protected:
    virtual void WriteInIndexFile(T fileName, T fileHash) {
        ofstream index(string(this->path->data()) + "/Index", ios_base::app);

        index << endl << "add" << " " << fileHash << " " << fileName;

        if (index.is_open()) {
            Logger::getInstance()->LogInformation("New line in Index file - add" + fileHash + " " + fileName);
        } else {
            Logger::getInstance()->LogError("Can't create new line");
        }

        index.close();
    }

    virtual string GetFileString(string fileName) {
        ifstream file(string(Tools::getInstance()->path->data()) + "/" + fileName);
        string allText = "";
        string text = "";
        if (!file.is_open()) {
            for (int i = 0; i < Tools::getInstance()->subDirs->size(); i++) {
                file.open(string(Tools::getInstance()->path->data()) + "/" + Tools::getInstance()->subDirs->at(i) + "/" + fileName);
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

    virtual void AddOldVersion(string name, string fileString, string hashName) {
        string folderPath = string(this->path->data()) + "/versions/";

        ofstream file(folderPath + hashName);
        if (!file.is_open()) {
            Logger::getInstance()->LogError("Ошибка при открытии файла");
        }
        file << endl << fileString;
        Logger::getInstance()->LogInformation("Добавена версия файла " + name);
    }

    void WriteAllFilesInBranchIndexFile(){
//        this->CreateNewBranch();
    }
public:
    ~NewChangeBase(){
//        delete files;
        delete hashNames;
        delete path;
    }
};


class NewChangeBuilder{
public:
    template <typename T, typename Y>
    void Build(NewChangeBase<T,Y> *newChangeBase){
        newChangeBase->createObjectDirectory();
        newChangeBase->CreateDirsWithHashTitle();
    }
};

class NewChangeDot: public NewChangeBase<string, vector<string>> {

public:
    NewChangeDot() {
        this->files = Tools::getInstance()->ReadAllFilesInDir();
        this->hashNames = new vector<string>{};
    }
    virtual bool CreateDirsWithHashTitle() override {
        ifstream dir;
        bool isCreated = true;

        for (int i = 0; i < this->files.size(); i++) {
            dir.open(string(this->path->data()) + "/objects/" + this->hashNames->at(i));
            if (!dir.is_open()) {
                Logger::getInstance()->LogError(
                        "Directory " + this->files.at(i) + " didn't create");
                isCreated = false;
            } else {
                WriteInIndexFile(this->files.at(i), this->hashNames->at(i));
                ofstream file(string(this->path->data()) + "/objects/" + this->hashNames->at(i) + "/" + this->hashNames->at(i));
                if (!file) {
                    Logger::getInstance()->LogError(
                            "file " + this->files.at(i) + " didn't add in " + this->hashNames->at(i));
                }
                file << this->GetFileString(this->files.at(i));
                AddOldVersion(this->files.at(i), this->GetFileString(this->files.at(i)), this->hashNames->at(i));

            }
        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("Directory created successfully");
        }

        return isCreated;
    }

public:
    ~NewChangeDot() {}
};

class NewChangeForFile: public NewChangeBase<string, vector<string>>{
public:
    NewChangeForFile(){
        this->files = Tools::getInstance()->ReadAllFilesInDir();
        this->hashNames = new vector<string>{};
    }
};


#endif //STN_NEWCHANGE_H
