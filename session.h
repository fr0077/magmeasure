#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <ctime>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Session
{
public:
    const boost::uuids::uuid id = boost::uuids::random_generator()();
    Session(std::string name);
    void close();
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

    std::string axis_order;

    double deltax;
    double deltay;
    double deltaz;
};

#endif // SESSION_H
