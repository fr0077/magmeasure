#ifndef SESSION_RESUME_DIALOG_H
#define SESSION_RESUME_DIALOG_H

#include <QDialog>

namespace Ui {
class session_resume_dialog;
}

class MainWindow;

class SessionResumeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionResumeDialog(QWidget *parent = nullptr);
    ~SessionResumeDialog();

    void setParent(MainWindow *mw){
        this->mw = mw;
    }

private slots:
    void on_pushButton_clicked();

private:
    Ui::session_resume_dialog *ui;
    MainWindow *mw;
};

#endif // SESSION_RESUME_DIALOG_H
