#include "probe.h"
#include <boost/algorithm/string.hpp>
#include <QDebug>
#include <vector>

class Group3Probe : public Probe{
    ProbeErrorType initialize() {
        return ProbeErrorType::COMMAND_FAILED;
    }

    ProbeErrorType setZero(ProbeAxis axis){
        return ProbeErrorType::COMMAND_FAILED;
    }

    ProbeValue getValue(){
        Probe::ProbeValue value;
        value.status = ProbeErrorType::COMMAND_SUCCESS;

        std::string cmd = "./get_3axis.sh";
        FILE *fp = popen(cmd.c_str(), "r");
        char result[30];
        std::string str;

        while (fgets(result, sizeof(result), fp))
            str += result;

        pclose(fp);

        std::vector<std::string> axis;
        boost::split(axis, str, boost::is_space());

        value.x = std::stod(axis.at(0));
        value.y = std::stod(axis.at(1));
        value.z = std::stod(axis.at(2));

        return value;
    }
};
