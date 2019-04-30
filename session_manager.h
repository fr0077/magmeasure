#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <iomanip>
#include <QMainWindow>
#include <QLabel>
#include <QString>
#include "log.h"
#include "probe.h"
#include <ctime>
#include <vector>

class Session;

class SessionManager
{
private:
    Session* currentSession;
    QMainWindow *mw;
    void writeSessionParam();
    void clearSessionParam();
public:
    SessionManager(QMainWindow *mw);

    Session::Status getSessionStatus();
    void newSession();
    void closeSession();
    void startSession();
    void pauseSession();

    void log(Log l);
    void setActuatorPosition(double x, double y, double z);
    void setMeasuringPosition(double x, double y, double z);
    void setProbeValue(Probe::ProbeValue v);
    void set1AxisProbeValue(Probe::ProbeValue v);
    void setFinishedCommands(int finished);
};

#endif
