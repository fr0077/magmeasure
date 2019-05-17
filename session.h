#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QDebug>
#include <QApplication>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>
#include <list>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

class SessionManager;

class Session
{
public:
    Session(std::string name);
    void close();
    void start();
    void pause();
    std::string getName(){
        return name;
    }

    std::string getMagmeshName(){
        return magmesh_name;
    }

    std::string getActMeshName(){
        return actmesh_name;
    }

    std::string getCmdName(){
        return cmds_name;
    }

    std::string getDatafileName(){
        return datafile_name;
    }

    enum Status{
        NO_SESSION, READY, RUNNING, PAUSED, FINISHED
    };

    int getTotalCmds(){
        return total_cmd_nums;
    }

    double getXmin(){
        return xmin;
    }

    double getXmax(){
        return xmax;
    }

    double getYmin(){
        return ymin;
    }

    double getDx(){
        return deltax;
    }

    double getDy(){
        return deltay;
    }

    double getDz(){
        return deltaz;
    }

    double getYmax(){
        return ymax;
    }

    double getZmin(){
        return zmin;
    }

    double getZmax(){
        return zmax;
    }

    int getMeasureTime(){
        return msec_measure_time;
    }

    int getNumberOfMeasure(){
        return number_of_measure;
    }

    int getWaitTime(){
        return sec_wait_after_move;
    }

    int getSpeed(){
        return actuator_speed;
    }

    double getOriginX(){
        return actuator_origin_x;
    }

    double getOriginY(){
        return actuator_origin_y;
    }

    double getOriginZ(){
        return actuator_origin_z;
    }

    std::string getAxisOrder(){
        return axis_order;
    }

    void begin();

    void resume(int i);

private:
    int total_cmd_nums;

    void begin(int i);

    SessionManager *manager;

    Status checkStatus(){
        return READY;
    }

    std::string name;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;

    std::string magmesh_name;
    std::string actmesh_name;
    std::string cmds_name;
    std::string datafile_name;
    std::string logfile_name;

    int msec_measure_time;
    int sec_wait_after_move;
    int number_of_measure;

    int actuator_speed;

    std::string axis_order;

    double actuator_origin_x;
    double actuator_origin_y;
    double actuator_origin_z;

    double deltax;
    double deltay;
    double deltaz;

    template<typename T>
    T getValue(std::string sessionName, std::string propertyName, boost::property_tree::ptree pt){
        if (boost::optional<T> value = pt.get_optional<T>(sessionName + "." + propertyName)) {
            return value.get();
        } else {
        }
    }
};

#endif // SESSION_H
