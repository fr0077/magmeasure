#include "session_manager.h"

SessionManager::SessionManager(MainWindow *mw)
{
    this->mw = mw;
    Log(Log::LogLevel::VERBOSE, "SessionManager created").write();
}

SessionManager::~SessionManager(){
    delete currentSession;
}

void SessionManager::startSession(){
    currentSession->begin();
}

void SessionManager::resumeSession(){
    currentSession->resume();
}

void SessionManager::newSession(std::string name){
    currentSession = new Session(name);
    writeSessionParam();
}

void SessionManager::writeSessionParam(){
    QLabel *ql = mw->findChild<QLabel *>("session_name", Qt::FindChildrenRecursively);
    ql->setText(QString::fromStdString(currentSession->getName()));

    ql = mw->findChild<QLabel *>("xmin", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getXmin()));

    ql = mw->findChild<QLabel *>("xmax", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getXmax()));

    ql = mw->findChild<QLabel *>("ymin", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getYmin()));

    ql = mw->findChild<QLabel *>("ymax", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getYmax()));

    ql = mw->findChild<QLabel *>("zmin", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getZmin()));

    ql = mw->findChild<QLabel *>("zmax", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getZmax()));

    ql = mw->findChild<QLabel *>("dx", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getDx()));

    ql = mw->findChild<QLabel *>("dy", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getDy()));

    ql = mw->findChild<QLabel *>("dz", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getDz()));

    ql = mw->findChild<QLabel *>("act_origin", Qt::FindChildrenRecursively);
    char buf_originx[20];
    char buf_originy[20];
    char buf_originz[20];
    std::sprintf(buf_originx, "%.2f", currentSession->getOriginX());
    std::sprintf(buf_originy, "%.2f", currentSession->getOriginY());
    std::sprintf(buf_originz, "%.2f", currentSession->getOriginZ());
    ql->setText(QString::fromStdString(std::string(buf_originx) + ", "
                                       + std::string(buf_originy) + ", "
                                       + std::string(buf_originz)));

    ql = mw->findChild<QLabel *>("measure_time", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getMeasureTime()));

    ql = mw->findChild<QLabel *>("wait_time", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getWaitTime()));

    ql = mw->findChild<QLabel *>("number_of_measuring", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getNumberOfMeasure()));

    ql = mw->findChild<QLabel *>("speed", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getSpeed()));

    ql = mw->findChild<QLabel *>("measure_time", Qt::FindChildrenRecursively);
    ql->setText(QString::number(currentSession->getMeasureTime()));

    setTotalCommands(currentSession->getTotalCmds());
}

void SessionManager::setTotalCommands(int total){
    QLabel *ql = mw->findChild<QLabel *>("cmd_total", Qt::FindChildrenRecursively);
    ql->setText(QString::number(total));
}

void SessionManager::clearSessionParam(){
    mw->findChild<QLabel *>("session_name", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("xmin", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("xmax", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("ymin", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("ymax", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("zmin", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("zmax", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("dx", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("dy", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("dz", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("act_origin", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("measure_time", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("wait_time", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("number_of_measuring", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("cmd_total", Qt::FindChildrenRecursively)->clear();
    mw->findChild<QLabel *>("speed", Qt::FindChildrenRecursively)->clear();
}
