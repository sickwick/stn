//
// Created by Mikel Shcherbakov on 13.10.2019.
//

#ifndef STN_NEWCHANGE_H
#define STN_NEWCHANGE_H

#include <vector>
#include <string>
#include "NewBranch.h"

template<typename T, typename Y>
class NewChangeBase {
protected:
    Y files;
    Y *hashNames;
    T *path;
    T *file;
    T shortHashName;
public:
    NewChangeBase() : path(this->path = new string(string(Tools::getInstance()->path->data()) + ".stn")) {}

    virtual void createObjectDirectory() {
        for (int i = 0; i < this->files.size(); i++) {
            string fileName = to_string(Tools::getInstance()->
                    CreateHash(Tools::getInstance()->GetFileString(this->files.at(i))));
            this->hashNames->push_back(fileName);
            this->shortHashName = fileName.substr(0, 6);
            filesystem::create_directory(string(this->path->data()) + "/objects/" + shortHashName);
        }
    }

    virtual bool CreateDirsWithHashTitle() {}

protected:
    virtual void WriteInIndexFile(T fileName, T fileHash) {
        ofstream index(string(this->path->data()) + "/Index", ios_base::app);

        index << "add" << " " << fileHash << " " << fileName << endl;

        if (index.is_open()) {
            Logger::getInstance()->LogInformation("New line in Index file - add" + fileHash + " " + fileName);
        } else {
            Logger::getInstance()->LogError("Can't create new line");
        }

        index.close();
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

    void WriteAllFilesInBranchIndexFile() {
//        this->CreateNewBranch();
    }

public:
    ~NewChangeBase() {
//        delete files;
        delete hashNames;
        delete path;
    }
};


class NewChangeBuilder {
public:
    template<typename T, typename Y>
    void Build(NewChangeBase<T, Y> *newChangeBase) {
        newChangeBase->createObjectDirectory();
        newChangeBase->CreateDirsWithHashTitle();
    }
};

class NewChangeDot : public NewChangeBase<string, vector<string>> {
public:
    NewChangeDot() {
        this->files = Tools::getInstance()->ReadAllFilesInDir();
        this->hashNames = new vector<string>{};
    }

    virtual bool CreateDirsWithHashTitle() override {
        ifstream dir;
        bool isCreated = true;

        for (int i = 0; i < this->files.size(); i++) {
            this->shortHashName = this->hashNames->at(i).substr(0, 6);
            dir.open(string(this->path->data()) + "/objects/" + this->shortHashName);
            if (!dir.is_open()) {
                Logger::getInstance()->LogError(
                        "Directory " + this->files.at(i) + " didn't create");
                isCreated = false;
            } else {
                WriteInIndexFile(this->files.at(i), this->shortHashName);
                ofstream file(string(this->path->data()) + "/objects/" + this->shortHashName + "/" +
                              this->shortHashName);
                if (!file) {
                    Logger::getInstance()->LogError(
                            "file " + this->files.at(i) + " didn't add in " + this->shortHashName);
                }
                file << this->hashNames->at(i);
                AddOldVersion(this->files.at(i), Tools::getInstance()->GetFileString(this->files.at(i)),
                              this->shortHashName);

            }
        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("Directory created successfully");
        }

        dir.close();

        return isCreated;
    }

public:
    ~NewChangeDot() {}
};

class NewChangeForFile : public NewChangeBase<string, vector<string>> {
private:
    string fileName;
public:
    NewChangeForFile(string arg) {
        this->file = new string(arg);
        this->hashNames = new vector<string>{};
    }

    virtual void createObjectDirectory() override {
        this->fileName = to_string(Tools::getInstance()->
                CreateHash(Tools::getInstance()->GetFileString(this->file->data())));
        this->hashNames->push_back(this->fileName);
        this->shortHashName = this->hashNames->at(0).substr(0, 6);
        filesystem::create_directory(string(this->path->data()) + "/objects/" + this->shortHashName);

    }

    virtual bool CreateDirsWithHashTitle() override {
        ifstream dir;
        bool isCreated = true;
        cout << shortHashName;
        dir.open(string(this->path->data()) + "/objects/" + this->shortHashName);
        if (!dir.is_open()) {
            Logger::getInstance()->LogError(
                    "Directory " + string(this->file->data()) + " didn't create");
            isCreated = false;
        } else {

            WriteInIndexFile(this->file->data(), this->shortHashName);
            ofstream file(
                    string(this->path->data()) + "/objects/" + this->shortHashName + "/" + this->shortHashName);
            if (!file) {
                Logger::getInstance()->LogError(
                        "file " + string(this->file->data()) + " didn't add in " + this->shortHashName);
            }
            file << this->fileName;
            AddOldVersion(string(this->file->data()), Tools::getInstance()->GetFileString(string(this->file->data())),
                          this->shortHashName);

        }

        if (isCreated) {
            Logger::getInstance()->LogInformation("Directory created successfully");
        }

        dir.close();

        return isCreated;
    }
};


#endif //STN_NEWCHANGE_H
