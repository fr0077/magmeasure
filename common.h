#ifndef COMMON_H
#define COMMON_H

#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdio>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

class Common{
public:
    static void msleep(unsigned int ms){
        usleep(ms*1000);
    }

    static std::string time_str()
    {
        const boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        const boost::posix_time::time_duration td = now.time_of_day();
        const long hours        = td.hours();
        const long minutes      = td.minutes();
        const long seconds      = td.seconds();
        const long milliseconds = td.total_milliseconds() -
                ((hours * 3600 + minutes * 60 + seconds) * 1000);

        char buf[40];
        sprintf(buf, "%02ld:%02ld:%02ld.%03ld",
                hours, minutes, seconds, milliseconds);

        return buf;
    }

    static std::string date_str(){
        time_t t = time(nullptr);

        const tm* lt = localtime(&t);

        std::stringstream s;
        s<<"20";
        s<<lt->tm_year-100;
        s<<"-";
        s<<lt->tm_mon+1;
        s<<"-";
        s<<lt->tm_mday;

        std::string result = s.str();
        return result;
    }

    static std::string date_time(){
        return date_str() + " " + time_str();
    }
};

#endif // COMMON_H
