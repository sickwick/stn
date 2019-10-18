//
// Created by Mikel Shcherbakov on 13.10.2019.
//

#ifndef STN_TOOLS_H
#define STN_TOOLS_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;
class Tools{
private:
    Tools(){}
    Tools(const Tools&);
    Tools& operator = (Tools&);
    static Tools * p_instance;
public:
    static Tools* getInstance(){
        if(!p_instance)
            p_instance = new Tools();
        return p_instance;
    }

protected:
    vector<string> *operations = new vector<string>{"add", "commit"};;
    vector<string> *files = new vector<string>{};
    vector<string> *words = new vector<string>{};

public:
    string path = "/Users/mike/CLionProjects/stn";

    bool CheckLine(string name, string operation, string arg) {
        bool flag = false;
        if (name == "stn") {
            for (int i = 0; i < this->operations->size(); i++) {
                if (operation == operations->at(i)) {
                    flag = true;
                }
            }

            if (flag) {
                if (arg != ".") {
                    return this->SearchFileFromDir("main");
                }
            }
        } else {
            cout << endl << "Неизвестная команда - " << name;
            return false;
        }

        return false;
    }

    string CutString(string longPath) {
        string shortPath;
        string currentWord = "";

        this->words->clear();
        longPath += "/";
        for (int i = 0; i < longPath.length(); i++) {
            if (longPath[i] == '/' || longPath[i] == longPath.length() - 1) {
                this->words->push_back(currentWord);
                currentWord = "";
            } else {
                currentWord += longPath[i];
            }
        }

        return this->words->at(this->words->size() - 1);
    }

    bool SearchFileFromDir(string fileName) {
        // TODO найти нормальный способ поиска файлов
        for (const auto &entry : fs::directory_iterator(this->path)) {
            this->files->push_back(CutString(entry.path()));
            if (this->CutString(entry.path()) == fileName) {
                return true;
            }
        }

        return false;
    }

    void ReadAllFiles() {
        ifstream file;
        ofstream newfile;
        string text;
        string allText = "";

        for (int i = 0; i < this->files->size(); i++) {
            allText = "";
            string filePath = this->path + "/" + this->files->at(i);
            file.open(filePath);
            if (!file.is_open()) {
                cout << "oshibka";
            }

            while (getline(file, text)) {
                allText += text;
            }
            newfile.open(path + "/" + to_string(this->CreateHash(allText)));
            newfile.close();
            file.close();
        }
    }

    size_t CreateHash(string fileString) {
        hash<string> fileHash;
        return fileHash(fileString);
    }

    //TODO: create this func. Index file path can find in Initialize.h

    void ModifyIndex(string operation, string blob){

    }



//    virtual ~Tools() {
//        this->words->clear();
//        this->files->clear();
//        this->operations->clear();
//    }
};


#endif //STN_TOOLS_H


