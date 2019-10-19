//
// Created by Mikel Shcherbakov on 18.10.2019.
//

#ifndef STN_LOGGER_H
#define STN_LOGGER_H

#include <fstream>
#include <ctime>

class Logger {
private:
    Logger() {}

    Logger(const Logger &);

    Logger &operator=(Logger &);

    static Logger *p_instance;
public:
    static Logger *getInstance() {
        if (!p_instance)
            p_instance = new Logger();
        return p_instance;
    }

private:
    string loggerPath = Tools::getInstance()->path + "/.stn/logs";
    ofstream loggerFile;
public:
    void LogInformation(string stringForLog) {
        loggerFile.open(this->loggerPath + "/information", ios_base::app);
        loggerFile << "--INFORMATION--" << " " << stringForLog << endl;
        loggerFile.close();
    }

    void LogError(string stringForLogError) {
        loggerFile.open(this->loggerPath + "/errors", ios_base::app);
        loggerFile << "--ERROR--" << " " << stringForLogError << endl;
        loggerFile.close();
    }
};

#endif //STN_LOGGER_H
