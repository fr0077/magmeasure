#ifndef MANAGER_H
#define MANAGER_H

#include "session.h"
#include <ctime>
#include <vector>

class Manager
{
private:
    std::vector<Session*>* sessions;
    Session* currentSession;

public:
    Manager();
    bool isSessionRunning();
    Session* getCurrentSession();
    Session* newSession();
    std::vector<Session> getSessionList();
    void closeSession();
};

#endif // MANAGER_H
