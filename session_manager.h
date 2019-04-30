#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <iostream>
#include <fstream>
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
    Session *currentSession = nullptr;
    QMainWindow *mw;
    void writeSessionParam();
    void clearSessionParam();
public:
    SessionManager(QMainWindow *mw);
    ~SessionManager();

    Session::Status getSessionStatus();
    void newSession(std::string name);
    void closeSession();
    void startSession();
    void pauseSession();

    void setActuatorPosition(double x, double y, double z);
    void setMeasuringPosition(double x, double y, double z);
    void setProbeValue(Probe::ProbeValue v);
    void set1AxisProbeValue(Probe::ProbeValue v);
    void setFinishedCommands(int finished);
};

#endif
