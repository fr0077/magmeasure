#ifndef MANAGER_H
#define MANAGER_H

#include "session.h"

class Manager
{
public:
    Manager();
    bool isSessionRunning();
    Session getCurrentSession();
    Session newSession();
};

#endif // MANAGER_H
