#include "mainwindow.h"
#include "session_manager.h"
#include "session_select_dialog.h"

class SessionManager;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new SessionManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;

    time_t time = std::time(nullptr);
    char s_time[256];
    std::tm *ptm = std::localtime(&time);
    strftime(s_time, 256, "%Y-%m-%d-%H-%M-%S", ptm);
    std::string cmd = "mv LOG LOG_";
    cmd += s_time;
    FILE *fp = popen(cmd.c_str(), "r");
    pclose(fp);
}

void MainWindow::on_button_session_create_clicked()
{
    if(manager->getSessionStatus() == Session::RUNNING ||
            manager->getSessionStatus() == Session::PAUSED){
        QMessageBox msgbox(this);
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setText(tr("すでにセッションが実行中です"));
        msgbox.setStandardButtons(QMessageBox::Ok);
        msgbox.exec();
        return;
    }

    SessionSelectDialog d;
    d.setParent(this);
    QListWidget *ql = d.findChild<QListWidget *>("session_list", Qt::FindChildrenRecursively);

    QStringList listItemText;

    boost::property_tree::ptree pt;
    boost::property_tree::read_ini("sessions.ini", pt);
    for(auto& section : pt){
        listItemText << QString::fromStdString(section.first);
    }

    ql->addItems(listItemText);

    d.exec();
}

void MainWindow::on_session_selected(std::string name){
    manager->newSession(name);
}

void MainWindow::on_button_session_abort_clicked()
{
    if(manager->getSessionStatus() != Session::RUNNING){
        return;
    }

    QMessageBox msgbox(this);
    msgbox.setIcon(QMessageBox::Warning);
    msgbox.setText(tr("本当にセッションを終了しますか？"));
    msgbox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    int response = msgbox.exec();
    if(response == QMessageBox::Ok){
        manager->closeSession();
        return;
    }
    return;
}

void MainWindow::on_button_session_start_clicked()
{
    if(manager->getSessionStatus() == Session::RUNNING){
        return;
    }

    if(manager->getSessionStatus() == Session::NO_SESSION){
        QMessageBox msgbox(this);
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setText(tr("セッションが選択されていません"));
        msgbox.setStandardButtons(QMessageBox::Ok);
        return;
    }

    if(manager->getSessionStatus() == Session::FINISHED){
        QMessageBox msgbox(this);
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setText(tr("終了済みのセッションです"));
        msgbox.setStandardButtons(QMessageBox::Ok);
        return;
    }

    if(manager->getSessionStatus() == Session::READY
            || manager->getSessionStatus() == Session::PAUSED){
        manager->startSession();
        return;
    }
}

void MainWindow::on_button_session_pause_clicked()
{

}
