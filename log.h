#ifndef LOG_H
#define LOG_H

#include "session.h"
#include <boost/uuid/uuid.hpp>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

class Log
{

public:
    enum LogLevel{
        FATAL,WARN,INFO,VERBOSE
    };
    Log(LogLevel loglevel, Session *session, std::string message){
        this->loglevel = loglevel;
        if(session != nullptr){
            this->session_name = session->getName();
        }else{
            this->session_name = "-";
        }

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

        char s_time[256];
        std::tm *ptm = std::localtime(&time);
        strftime(s_time, 256, "%Y-%m-%d %H:%M:%S", ptm);

        return std::string(s_time) + "\t" + logLevel + "\t" + session_name + "\t" + message + "\n";
    }
private:
    LogLevel loglevel;
    std::string session_name;
    std::string message;
    std::time_t time;
};

#endif // LOG_H
