#include "mainwindow.h"


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
}

void MainWindow::on_button_session_create_clicked()
{
    if(manager->getSessionStatus() == Session::RUNNING){
        QMessageBox msgbox(this);
        msgbox.setIcon(QMessageBox::Warning);
        msgbox.setText(tr("すでにセッションが実行中です"));
        msgbox.setStandardButtons(QMessageBox::Ok);
        msgbox.exec();
        return;
    }
    manager->newSession();
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
        //TODO: Start session
        return;
    }
}

void MainWindow::on_button_session_pause_clicked()
{

}
