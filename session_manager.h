#ifndef MANAGER_H
#define MANAGER_H

#include "session.h"
#include <QMainWindow>
#include <QLabel>
#include "probe.h"
#include <ctime>
#include <vector>

class SessionManager
{
private:
    Session* currentSession;
    QMainWindow *mw;

public:
    SessionManager(QMainWindow *mw);

    bool isSessionRunning();
    Session* getCurrentSession();
    Session* newSession();
    void closeSession();

    void setActuatorErrorStatus(char status);
    void setActuatorPosition(double x, double y, double z);
    void setMeasuringPosition(double x, double y, double z);
    void setProbeValue(Probe::ProbeValue v);
    void setFinishedCommands(int finished);
};

#endif // MANAGER_H
