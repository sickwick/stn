//
// Created by Mikel Shcherbakov on 06.11.2019.
//

#ifndef STN_NEWBRANCH_H
#define STN_NEWBRANCH_H

class NewBranch {
private:
    string branchDir = Tools::getInstance()->path + "/.stn/branches";
public:
    NewBranch() {}

protected:
    bool CreateNewBranch(string branchName) {
        int dir = filesystem::create_directory(this->branchDir + "/" + branchName);
        if (!dir) {
            Logger::getInstance()->LogError("Не удалось создать ветку  " + branchName);
            return false;
        }
        Logger::getInstance()->LogInformation("Создана новая ветвь - " + branchName);

        ofstream file(branchDir + "/" + branchName + "/Index");
        if (!file.is_open()) {
            Logger::getInstance()->LogError("Не удалось создать файл - Index в " + branchDir + "/" + branchName);
        }
        return true;
    }

    bool CechoutToBranch(string branchName) {

    }
};

#endif //STN_NEWBRANCH_H
