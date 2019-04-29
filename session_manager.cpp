#include "session_manager.h"

SessionManager::SessionManager(QMainWindow *mw)
{
    currentSession = nullptr;
    this->mw = mw;
    QLabel *ql = mw->findChild<QLabel *>("session_name", Qt::FindChildrenRecursively);
    ql->setText("Set!");
}

Session* SessionManager::getCurrentSession(){
    return currentSession;
}

bool SessionManager::isSessionRunning(){
    return currentSession != nullptr;
}

void SessionManager::closeSession(){
    if(isSessionRunning()){
        currentSession->close();
    }
    currentSession = nullptr;
}

Session* SessionManager::newSession(){
    if(isSessionRunning())
        throw "Sesseion already running";
    Session* session = new Session("test");
    currentSession = session;
    return session;
}
