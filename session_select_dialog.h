#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QModelIndexList>
#include <QDebug>
#include <iostream>
#include "log.h"
#include "ui_session_select_dialog.h"

class MainWindow;
class SessionManager;

namespace Ui {
class SessionSelectDialog;
}

class SessionSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionSelectDialog(QWidget *parent = nullptr);
    void setManager(SessionManager *manager){
        this->manager = manager;
    }
    ~SessionSelectDialog();

    void setParent(MainWindow *mw){
        this->parent = mw;
    }

private slots:
    void on_session_list_clicked(const QModelIndex &index);

    void on_cancel_clicked();

    void on_ok_clicked();

private:
    Ui::SessionSelectDialog *ui;
    SessionManager *manager;
    std::string selected_session;
    MainWindow *parent;
};

#endif // DIALOG_H
