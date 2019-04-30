#include "session.h"

Session::Session(std::string name)
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini("sessions.ini", pt);

    qDebug() << QApplication::applicationDirPath();

    if (boost::optional<int> value = pt.get_optional<int>("session1.xmin")) {
        qDebug() << value.get();
    }
    else {
        qDebug() << "no value";
    }
}

void Session::close(){
    closed = true;
}
