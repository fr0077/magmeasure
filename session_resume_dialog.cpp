#include "session_resume_dialog.h"
#include "ui_session_resume_dialog.h"
#include "mainwindow.h"

SessionResumeDialog::SessionResumeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::session_resume_dialog)
{
    ui->setupUi(this);
}

SessionResumeDialog::~SessionResumeDialog()
{
    delete ui;
}

void SessionResumeDialog::on_pushButton_clicked()
{
    QLineEdit *ql = this->findChild<QLineEdit *>("lineEdit", Qt::FindChildrenRecursively);

    QString text = ql->text();
    mw->on_cmd_num_entered(std::atoi(text.toStdString().c_str()));
    close();
}
