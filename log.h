#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <fstream>
#include "common.h"

class Log
{

public:
    enum LogLevel{
        FATAL,WARN,INFO,VERBOSE
    };

    Log(LogLevel loglevel, std::string message){
        this->loglevel = loglevel;

        this->message = message;
        this->time = std::time(nullptr);
    }

    void write(){
        std::ofstream out("LOG", std::ios::app);
        out << this->toString();
        out.close();
    }

    std::string toString(){
        std::string logLevel;
        if(loglevel == FATAL)
            logLevel = "FATAL";
        if(loglevel == WARN)
            logLevel = "WARN";
        if(loglevel == INFO)
            logLevel = "INFO";
        if(loglevel == VERBOSE)
            logLevel = "VERBOSE";

        return Common::date_time() + "\t" + logLevel + "\t" + message + "\n";
    }
private:
    LogLevel loglevel;
    std::string message;
    std::time_t time;
};

#endif // LOG_H
