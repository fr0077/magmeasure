#ifndef LOG_H
#define LOG_H

#include "session.h"
#include <boost/uuid/uuid.hpp>
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
        this->session_name = session.getName();
        this->session_uuid = session.id;

        this->message = message;
        this->time = time;
    }
private:
    LogLevel loglevel;
    std::string session_name;
    boost::uuids::uuid session_uuid;
    std::string message;
    std::time_t time;
};

#endif // LOG_H
