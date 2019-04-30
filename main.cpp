#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //FILE *fp = popen("./meshgen 2 > test", "r");
    //pclose(fp);

    return a.exec();
}
