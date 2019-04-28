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
    Log(LogLevel loglevel, Session session, std::string message);
};

#endif // LOG_H
