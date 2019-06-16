#include "probe.h"
#include <unistd.h>
#include <QDebug>

class Group3OneAxisProbe : public Probe{
    ProbeErrorType initialize() {
        return ProbeErrorType::COMMAND_SUCCESS;
    }

    ProbeErrorType setZero(ProbeAxis axis){
        return ProbeErrorType::COMMAND_FAILED;
    }

    ProbeValue getValue(){
        std::string cmd = "./get_1axis.sh";
        FILE *fp = popen(cmd.c_str(), "r");
        char result[30];
        std::string str;
        Probe::ProbeValue value;

        while (fgets(result, sizeof(result), fp))
            str += result;

        qDebug() << QString::fromStdString(str);
        value.status = ProbeErrorType::COMMAND_SUCCESS;

        value.x = 4;
        value.y = 0;
        value.z = 0;

        return value;
    }
};
