#include "mainwindow.h"
#include "session_manager.h"

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
    std::string cmd = "mv LOG logs/LOG_";
    cmd += s_time;
    FILE *fp = popen(cmd.c_str(), "r");
    pclose(fp);
}

void MainWindow::on_button_session_create_clicked()
{
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

void MainWindow::on_button_session_start_clicked()
{
    manager->startSession();
}

void MainWindow::on_resume_clicked()
{
    if(manager->getCurrentSession() == nullptr)
        return;
    SessionResumeDialog d;
    d.setParent(this);
    d.exec();
}

void MainWindow::on_cmd_num_entered(int num){
    if(manager->getCurrentSession() == nullptr)
        return;

    QMessageBox msgBox(this);
    std::string msg = manager->getCurrentSession()->getActMeshName() + "の" + std::to_string(num - 1) + "行目の位置にアクチュエーターを動かし、OKをクリックしてください";
    msgBox.setText(tr(msg.c_str()));
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    int res = msgBox.exec();

    if(res == QMessageBox::No){
        return;
    }

    if(res == QMessageBox::Yes){
        manager->resumeSession(num);
    }
}
