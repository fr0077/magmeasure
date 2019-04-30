#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "session_manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
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
