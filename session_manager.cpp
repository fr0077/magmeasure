#include "session_manager.h"

SessionManager::SessionManager(QMainWindow *mw)
{
    currentSession = nullptr;
    this->mw = mw;
    QLabel *ql = mw->findChild<QLabel *>("session_name", Qt::FindChildrenRecursively);
    log(Log(Log::LogLevel::VERBOSE, currentSession, time(nullptr), "SessionManager created"));
    ql->setText("No session running");
}

bool SessionManager::isSessionRunning(){
    return currentSession != nullptr;
}

void SessionManager::log(Log l){

}

void SessionManager::closeSession(){
    if(isSessionRunning()){
        currentSession->close();
    }
    currentSession = nullptr;
    QLabel *ql = mw->findChild<QLabel *>("session_name", Qt::FindChildrenRecursively);
    ql->setText("No session running");
}

void SessionManager::newSession(){
    if(isSessionRunning())
        throw "Sesseion already running";
    std::string session_name = "session1";
    Session* session = new Session(session_name);
    QLabel *ql = mw->findChild<QLabel *>("session_name", Qt::FindChildrenRecursively);
    ql->setText(QString::fromStdString(session_name));
    currentSession = session;
}
