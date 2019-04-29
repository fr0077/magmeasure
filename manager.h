#ifndef MANAGER_H
#define MANAGER_H

#include "session.h"
#include "probe.h"
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

    void setActuatorErrorStatus(char status);
    void setActuatorPosition(double x, double y, double z);
    void setMeasuringPosition(double x, double y, double z);
    void setProbeValue(Probe::ProbeValue v);
    void setFinishedCommands(int finished);
};

#endif // MANAGER_H
