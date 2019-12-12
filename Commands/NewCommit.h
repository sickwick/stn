//
// Created by Mikel Shcherbakov on 06.11.2019.
//

#ifndef STN_NEWCOMMIT_H
#define STN_NEWCOMMIT_H

#include <ctime>

class NewCommit {
private:
    string *path = new string(string(Tools::getInstance()->path->data()) + ".stn");

public:
    NewCommit(string message) {
        this->CreateCommitFolder(message);
    }

protected:
    template<typename T>
    void CreateCommitFolder(T commit) {
        int seconds = time(NULL) / 3600;
        int branchNameHash = Tools::getInstance()->CreateHash(commit);
        int folderName = seconds + branchNameHash;

        bool result = this->WriteHashInBranchFile(folderName, commit);

        if (result) {
            ifstream Index(string(this->path->data()) + "/Index", ios::in | ios::out);
            Index.close();

            ofstream index(string(this->path->data()) + "/Index");
            index << "commit " << commit << "\n" <<folderName;
            index.close();
        }

    }

    template<typename T, typename Y>
    bool WriteHashInBranchFile(T folderName, Y commit) {
        filesystem::create_directory(string(this->path->data()) + "/objects/" + to_string(folderName));

        ifstream directory(string(this->path->data()) + "/objects/" + to_string(folderName));
        ifstream Index(string(this->path->data()) + "/Index");
        ofstream dir(string(this->path->data()) + "/objects/" + to_string(folderName) + "/" + to_string(folderName));
        bool isCreated = false;

        if (!directory.is_open()) {
            Logger::getInstance()->LogError("Directory " + to_string(folderName) + " didn't create");
        } else if (!Index.is_open()) {
            Logger::getInstance()->LogError("File Index didn't open");
        } else if (!dir.is_open()) {
            Logger::getInstance()->LogError("File " + to_string(folderName) + " didn't open");
        } else {
            dir << this->FormatIndexFile(Tools::getInstance()->GetFileString(".stn/Index"), commit);
            isCreated = true;
        }

        directory.close();
        dir.close();
        Index.close();

        return isCreated;
    }

private:
    string FormatIndexFile(string fileString, string commit) {
        string result = "commit " + commit;
        for (int i = 0; i < fileString.length() - 4; i++) {
            string word = fileString.substr(i, 1) + fileString.substr(i + 1, 1) + fileString.substr(i + 2, 1);
            if (word == "add") {
                result += "\n";
            }
            result += fileString[i];
        }

        return result;
    }
};

#endif //STN_NEWCOMMIT_H
