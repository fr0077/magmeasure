#include "actuator.h"
#include <boost/algorithm/string.hpp>
#include <QDebug>

class ThkActuator : public Actuator{

private:
    std::vector<std::string> getResult(std::string cmd){
        FILE *fp = popen(cmd.c_str(), "r");
        char result[30];
        std::string str;
        while (fgets(result, sizeof(result), fp))
            str += result;
        pclose(fp);

        std::vector<std::string> results;
        boost::split(results, str, boost::is_space());

        return results;
    }

    std::map<ActuatorAxis, int> speed;
    std::map<ActuatorAxis, int> dist;

public:

    ThkActuator(int xmax, int ymax, int zmax) : Actuator(xmax, ymax, zmax){}

    Actuator_Error_Type init(ActuatorAxis axis){
        std::string cmd = "./stage/init.py " + Actuator::axis_toString(axis);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01")
            type = COMMAND_SUCCESS;
        else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    Actuator_Error_Type resetAlarm(ActuatorAxis axis){
        std::string cmd = "./stage/reset_error.py " + Actuator::axis_toString(axis);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01")
            type = COMMAND_SUCCESS;
        else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    ActuatorResponse getAlarm(ActuatorAxis axis){
        std::string cmd = "./stage/get_error.py " + Actuator::axis_toString(axis);

        std::vector<std::string> result = getResult(cmd);

        ActuatorResponse response;

        if(result.at(0) == "TIMEOUT")
            response.errType = TIMED_OUT;
        else {
            response.errType = COMMAND_SUCCESS;
        }

        response.response = result;
        return response;
    }

    ActuatorResponse getServoStatus(ActuatorAxis axis){
        ActuatorResponse ret;
        ret.errType = COMMAND_FAILED;
        return ret;
    }

    ActuatorResponse getCurrentPosition(ActuatorAxis axis){
        ActuatorResponse ret;

        std::string cmd = "./stage/get_current_position.py " + Actuator::axis_toString(axis);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "TIMEOUT")
            type = TIMED_OUT;
        else{
            std::string bytes = result.at(0).substr(0,8);
            qDebug() << QString::fromStdString(bytes);
        }

        for(int i = 1; i < result.size() - 1; i++){
            ret.response.push_back(result.at(i));
        }

        return ret;
    }

    ActuatorResponse getZeroingCompleted(ActuatorAxis axis){
        ActuatorResponse ret;
        ret.errType = COMMAND_FAILED;
        return ret;
    }

    Actuator_Error_Type setSpeed(ActuatorAxis axis, int speed){
        this->speed[axis] = speed;

        std::string cmd = "./stage/set_speed.py " + Actuator::axis_toString(axis) + " ";
        cmd += std::to_string(speed);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01")
            type = COMMAND_SUCCESS;
        else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    Actuator_Error_Type setDistance(ActuatorAxis axis, int distance){
        this->dist[axis] = distance;

        std::string cmd = "./stage/set_dist.py " + Actuator::axis_toString(axis) + " ";
        cmd += std::to_string(distance);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01")
            type = COMMAND_SUCCESS;
        else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    Actuator_Error_Type move(ActuatorAxis axis, Direction dir){

        if(axis == ACTUATOR_AXIS_Y){
            if(dir == POSITIVE)
                dir = NEGATIVE;
            else {
                dir = POSITIVE;
            }
        }

        std::string cmd = "./stage/move.py " + Actuator::axis_toString(axis) + " " + direction_toString(dir);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01"){
            type = COMMAND_SUCCESS;
            sleep(int(estimateTime(axis) + 1));
        }else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    Actuator_Error_Type zero(ActuatorAxis axis){
        std::string cmd = "./stage/zero.py " + Actuator::axis_toString(axis);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01")
            type = COMMAND_SUCCESS;
            if(axis == ACTUATOR_AXIS_X || axis == ACTUATOR_AXIS_Z)
                sleep(30);
            if(axis == ACTUATOR_AXIS_Y)
                sleep(60);
        else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    Actuator_Error_Type servoOn(ActuatorAxis axis){
        std::string cmd = "./stage/servo_on.py " + Actuator::axis_toString(axis);

        std::vector<std::string> result = getResult(cmd);
        Actuator_Error_Type type;

        if(result.at(0) == "01")
            type = COMMAND_SUCCESS;
        else if(result.at(0) == "00"){
            type = COMMAND_FAILED;
        }else{
            type = TIMED_OUT;
        }

        return type;
    }

    double estimateTime(ActuatorAxis axis){
        return dist[axis] / 1000.0 / speed[axis];
    }
};