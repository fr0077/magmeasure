#ifndef LOG_H
#define LOG_H

#include "session.h"
#include <string>
#include <ctime>

class Log
{

public:
    enum LogLevel{
        FATAL,WARN,INFO,VERBOSE
    };
    Log(LogLevel loglevel, Session session, std::time_t time, std::string message){
        this->loglevel = loglevel;
        this->session = session;
        this->message = message;
        this->time = time;
    }
private:
    LogLevel loglevel;
    Session session;
    std::string message;
    std::time_t time;
};

#endif // LOG_H
