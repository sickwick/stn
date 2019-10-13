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

class Tools {
protected:
    vector<string> *operations;
    vector<string> *files;
    vector<string> *words;

public:
    Tools() {
        operations = new vector<string>{"add", "commit"};
        files = new vector<string>{};
        words = new vector<string>{};
    }

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
        string path = "/Users/mike/CLionProjects/stn";
        for (const auto &entry : fs::directory_iterator(path)) {
            if (this->CutString(entry.path()) == fileName) {
                return true;
            }
        }

        return false;
    }

    virtual ~Tools() {
        this->words->clear();
        this->files->clear();
        this->operations->clear();
    }
};


#endif //STN_TOOLS_H
