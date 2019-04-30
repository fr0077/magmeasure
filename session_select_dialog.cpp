#include "session_select_dialog.h"
#include "ui_session_select_dialog.h"
#include "log.h"

SessionSelectDialog::SessionSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SessionSelectDialog)
{
    ui->setupUi(this);
}

SessionSelectDialog::~SessionSelectDialog()
{
    delete ui;
}

void SessionSelectDialog::on_session_list_clicked(const QModelIndex &index)
{
    QPushButton *ok = findChild<QPushButton *>("ok", Qt::FindChildrenRecursively);
    selected_session = index.data().toString().toStdString();
    ok->setEnabled(true);
}

void SessionSelectDialog::on_cancel_clicked()
{
    close();
}

void SessionSelectDialog::on_ok_clicked()
{
    parent->on_session_selected(selected_session);
    close();
}
