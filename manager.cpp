#include "manager.h"

Manager::Manager()
{
    sessions = new std::vector<Session*>;
    currentSession = nullptr;
}

Session* Manager::getCurrentSession(){
    if(!isSessionRunning()){
        return nullptr;
    }
    return currentSession;
}

bool Manager::isSessionRunning(){
    return currentSession != nullptr;
}

void Manager::closeSession(){
    if(isSessionRunning()){
        currentSession->close();
    }
    currentSession = nullptr;
}

Session* Manager::newSession(){
    if(isSessionRunning())
        throw "Sesseion already running";
    Session* session = new Session("test");
    sessions->push_back(session);
    currentSession = session;
    return session;
}
