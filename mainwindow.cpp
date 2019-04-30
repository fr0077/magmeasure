#include "mainwindow.h"
#include "session_select_dialog.h"

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
    QListView *ql = d.findChild<QListView *>("session_list", Qt::FindChildrenRecursively);
    QStandardItemModel * model = new QStandardItemModel();
    ql->setModel(model);

    QStringList listItemText;
    listItemText << "session1";
    listItemText << "chant";
    listItemText << "pray";
    listItemText << "invoke!";

    foreach ( QString text, listItemText )
    {
        QStandardItem * item = new QStandardItem();
        item->setText( text );
        item->setEditable( false );
        model->appendRow( item ); // リストビューはアイテムを列に追加
    }

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
        //TODO: Start session
        return;
    }
}

void MainWindow::on_button_session_pause_clicked()
{

}
