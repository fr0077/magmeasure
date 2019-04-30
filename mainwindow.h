#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "ui_session_select_dialog.h"
#include "session_manager.h"
#include <QStandardItemModel>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace Ui {
class MainWindow;
class SessionSelectDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void on_session_selected(std::string name);
    ~MainWindow();

private slots:

    void on_button_session_create_clicked();

    void on_button_session_abort_clicked();

    void on_button_session_start_clicked();

    void on_button_session_pause_clicked();

private:
    Ui::MainWindow *ui;
    SessionManager *manager;
};

#endif // MAINWINDOW_H
