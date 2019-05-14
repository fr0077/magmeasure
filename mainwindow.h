#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "ui_session_select_dialog.h"
#include <QStandardItemModel>
#include <list>
#include <QListWidget>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>
#include "session_select_dialog.h"
#include <QApplication>

class SessionManager;

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
    void on_button_session_start_clicked();
    void on_resume_clicked();

private:
    Ui::MainWindow *ui;
    SessionManager *manager;

};

#endif // MAINWINDOW_H
