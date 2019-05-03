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
    std::string cmd = "mv LOG LOG_";
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
