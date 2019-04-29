#include "probe.h"

class DummyProbe : public Probe
{
public:
    ProbeErrorType initialize(){
        return COMMAND_SUCCESS;
    }

    ProbeErrorType setZero(ProbeAxis axis){
        return COMMAND_SUCCESS;
    }

    Value getValue(){
        Value v;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        v.status = COMMAND_SUCCESS;
        return v;
    }
};
