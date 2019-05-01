#include "actuator.h"

class ThkActuator : public Actuator{
public:

    ThkActuator(int xmax, int ymax, int zmax) : Actuator(xmax, ymax, zmax){}

    Actuator_Error_Type resetAlarm(ActuatorAxis axis){
        return COMMAND_SUCCESS;
    }

    ActuatorResponse getAlarm(ActuatorAxis axis){
        ActuatorResponse ret;
        ret.errType = COMMAND_SUCCESS;
        ret.response.push_back(0xFF);
        return ret;
    }

    ActuatorResponse getServoStatus(ActuatorAxis axis){
        ActuatorResponse ret;
        ret.errType = COMMAND_SUCCESS;
        ret.response.push_back(0x01);

        return ret;
    }

    ActuatorResponse getCurrentPosition(ActuatorAxis axis){
        ActuatorResponse ret;
        ret.errType = COMMAND_SUCCESS;
        ret.response.push_back(0x00);
        ret.response.push_back(0x01);

        return ret;
    }

    ActuatorResponse getZeroingCompleted(ActuatorAxis axis){
        ActuatorResponse ret;
        ret.errType = COMMAND_SUCCESS;
        ret.response.push_back(0x01);

        return ret;
    }

    Actuator_Error_Type setSpeed(ActuatorAxis axis, int speed){
        return COMMAND_SUCCESS;
    }

    Actuator_Error_Type moveDistance(ActuatorAxis axis, int distance){
        return COMMAND_SUCCESS;
    }

    Actuator_Error_Type zero(ActuatorAxis axis){
        return COMMAND_SUCCESS;
    }
};
