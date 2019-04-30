#include "session.h"
#include "session_manager.h"

Session::Session(std::string name)
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini("sessions.ini", pt);

    this->name = name;
    xmin = getValue<double>(name, "xmin", pt);
    xmax = getValue<double>(name, "xmax", pt);
    ymin = getValue<double>(name, "ymin", pt);
    ymax = getValue<double>(name, "ymax", pt);
    zmin = getValue<double>(name, "zmin", pt);
    zmax = getValue<double>(name, "zmax", pt);

    deltax = getValue<double>(name, "deltax", pt);
    deltay = getValue<double>(name, "deltay", pt);
    deltaz = getValue<double>(name, "deltaz", pt);

    actuator_origin_x = getValue<double>(name, "actuator_origin_x", pt);
    actuator_origin_y = getValue<double>(name, "actuator_origin_y", pt);
    actuator_origin_z = getValue<double>(name, "actuator_origin_z", pt);

    axis_order = getValue<std::string>(name, "axis_order", pt);

    msec_measure_time = getValue<int>(name, "msec_measure_time", pt);
    msec_wait_after_move = getValue<int>(name, "msec_wait_after_move", pt);
    number_of_measure = getValue<int>(name, "number_of_measure", pt);
    actuator_speed = getValue<int>(name, "actuator_speed", pt);
}

void Session::close(){
    closed = true;
}

void Session::execute(){
    manager->setActuatorPosition(1,1,1);
}
