//
// Created by Mikel Shcherbakov on 13.10.2019.
//

#ifndef STN_TOOLS_H
#define STN_TOOLS_H

#include <fstream>
#include <filesystem>
#include <vector>
#include "Logger.h"

namespace fs = std::filesystem;

using namespace std;

class Tools {
private:
    Tools() {}

    Tools(const Tools &);

    Tools &operator=(Tools &);

    static Tools *p_instance;
public:
    static Tools *getInstance() {
        if (!p_instance)
            p_instance = new Tools();
        return p_instance;
    }

protected:
    vector<string> *files = new vector<string>{};
    vector<string> *words = new vector<string>{};
public:
    string mainBranch = "master";
    string currentBranch = mainBranch;
    vector<string> *operations = new vector<string>{"init", "add", "commit"};
    vector<string> *subDirs = new vector<string>{"objects", "versions", "logs", "branches"};
    vector<string> *fileNames = new vector<string>{"Index", "Current_branch", "Branches"};

    string *path = new string(GetCurrentPath());

    string CheckLine(string arg) {
        if (arg != ".") {
            return arg;
        }

        return "dot";
    }


    string CutPathString(string longPath) {
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
        for (const auto &entry : fs::directory_iterator(this->path->data())) {
            this->files->push_back(this->CutPathString(entry.path()));
            if (this->CutPathString(entry.path()) == fileName) {
                return true;
            }
        }

        return false;
    }

    vector<string> ReadAllFiles() {
        ifstream file;
        ofstream newfile;
        string text;
        string allText = "";

        for (int i = 0; i < this->files->size(); i++) {
            allText = "";
            string filePath = string(this->path->data()) + "/" + this->files->at(i);
            file.open(filePath);
            if (!file.is_open()) {
                cout << "oshibka";
            }

            while (getline(file, text)) {
                allText += text;
            }
            newfile.open(string(this->path->data()) + "/" + to_string(this->CreateHash(allText)));
            newfile.close();
            file.close();
        }

        return *this->files;
    }

    vector<string> ReadAllFilesInDir() {
        vector<string> filess;
        for (const auto &entry : fs::directory_iterator(string(this->path->data()))) {
            filess.push_back(this->CutPathString(entry.path()));
        }
        return filess;
    }

    size_t CreateHash(string fileString) {
        hash<string> fileHash;
        return fileHash(fileString);
    }

    string GetFileString(string fileName) {
        ifstream file(string(this->path->data()) + "/" + fileName);
        string allText = "";
        string text = "";
        if (!file.is_open()) {
            for (int i = 0; i < this->subDirs->size(); i++) {
                file.open(
                        string(this->path->data()) + "/" + this->subDirs->at(i) + "/" +
                        fileName);
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

    template<typename T>
    int FindOperationIndex(T operation) {
        if (operation == this->operations->at(0)) {
            return 0;
        } else if (operation == this->operations->at(1)) {
            return 1;
        } else if (operation == this->operations->at(2)) {
            return 2;
        }

        return 10;
    }

    template<typename T>
    bool ValidateIndex(T operation) {
        T indexContent = this->GetFileString(".stn/Index");

        int inputOperationIndex = this->FindOperationIndex(operation);
        int currentOperationIndex;

        if (indexContent.length() >= 5) {
            if (indexContent.substr(0, 5) == this->operations->at(2)) {
                currentOperationIndex = 2;
            }
        } else if (indexContent.length() >= 3) {
            if (indexContent.substr(0, 3) == this->operations->at(1)) {
                currentOperationIndex = 1;
            }
        }

        if (currentOperationIndex == inputOperationIndex) {
            return false;
        } else if (currentOperationIndex < inputOperationIndex) {
            return false;
        }

        return true;
    }

private:
    string GetCurrentPath() {
        string path = filesystem::current_path();
        for (int i = path.length() - 1; i > 0; i--) {
            if (path[i] == '/') {
                break;
            } else {
                path.erase(i, 1);
            }
        }
        return path;
    }

public:

    ~Tools() {
        this->words->clear();
        this->files->clear();
        this->operations->clear();
        this->subDirs->clear();
        this->fileNames->clear();
    }
};


#endif //STN_TOOLS_H


