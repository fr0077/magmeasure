#include "probe.h"
#include <unistd.h>

class Group3OneAxisProbe : public Probe{
    ProbeErrorType initialize() {
        usleep(100);
        return ProbeErrorType::COMMAND_SUCCESS;
    }

    ProbeErrorType setZero(ProbeAxis axis){
        usleep(100);
        return ProbeErrorType::COMMAND_SUCCESS;
    }

    ProbeValue getValue(){
        usleep(50);
        Probe::ProbeValue value;
        value.status = ProbeErrorType::COMMAND_SUCCESS;
        value.x = 4;
        value.y = 0;
        value.z = 0;

        return value;
    }
};
