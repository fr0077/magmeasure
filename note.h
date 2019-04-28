#ifndef NOTE_H
#define NOTE_H

#include <ctime>
#include "session.h"
#include <string>

class Note
{
private:
    Session session;
    std::time_t time;
    std::string text;

public:
    bool deletedFlag = false;
    bool starFlag = false;
    Note(Session session, std::time_t time, std::string text){
        this->session = session;
        this->time = time;
        this->text = text;
    }
};

#endif // NOTE_H
