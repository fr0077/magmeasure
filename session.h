#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QDebug>
#include <QApplication>
#include <ctime>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/optional.hpp>

class Session
{
public:
    const std::string id = boost::uuids::to_string(boost::uuids::random_generator()());
    Session(std::string name);
    void close();
    void start();
    void pause();
    std::string getName(){
        return name;
    }

private:
    bool closed = false;
    int total_line_nums;
    int finished_line_nums = 0;

    std::string name;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;

    double actuator_origin_x;
    double actuator_origin_y;
    double actuator_origin_z;

    enum AXIS_ORDER{
        XYZ,XZY,YXZ,YZX,ZXY,ZYX
    };

    AXIS_ORDER axisOrder;

    double deltax;
    double deltay;
    double deltaz;
};

#endif // SESSION_H
