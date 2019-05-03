#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <iostream>
#include <fstream>
#include <QLabel>
#include <QString>
#include "probe.h"
#include <ctime>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <vector>
#include "mainwindow.h"
#include "session.h"

class MainWindow;

class SessionManager
{
private:
    Session *currentSession = nullptr;
    MainWindow *mw;
    void writeSessionParam();
    void clearSessionParam();
public:
    SessionManager(MainWindow *mw);
    ~SessionManager();

    Session::Status getSessionStatus();
    void newSession(std::string name);
    void closeSession();
    void startSession();
    void pauseSession();
    void setTotalCommands(int total);
};

#endif
