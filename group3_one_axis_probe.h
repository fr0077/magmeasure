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

        fgets(result, sizeof(result), fp);
        str += result;
        pclose(fp);

        Probe::ProbeValue value;
        if(str.find("timed out") != std::string::npos){
            value.status = ProbeErrorType::TIMED_OUT;
            return value;
        }

        if(str.find("Network") != std::string::npos){
            value.status = ProbeErrorType::COMMAND_FAILED;
            return value;
        }

        value.status = ProbeErrorType::COMMAND_SUCCESS;

        value.x = std::stod(str);
        value.y = std::numeric_limits<double>::quiet_NaN();
        value.z = std::numeric_limits<double>::quiet_NaN();

        return value;
    }
};
