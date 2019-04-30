#ifndef MANAGER_H
#define MANAGER_H

#include <iomanip>
#include <QMainWindow>
#include <QLabel>
#include <QString>
#include "session.h"
#include "log.h"
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
    void newSession();
    void closeSession();
    void startSession();
    void pauseSession();

    void log(Log l);

    void setActuatorErrorStatus(char status);
    void setActuatorPosition(double x, double y, double z);
    void setMeasuringPosition(double x, double y, double z);
    void setProbeValue(Probe::ProbeValue v);
    void setFinishedCommands(int finished);
};

#endif
