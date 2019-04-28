#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new Manager;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_session_create_clicked()
{
    if(manager->isSessionRunning()){
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
    if(!manager->isSessionRunning()){
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
