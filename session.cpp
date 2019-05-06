#include "session.h"
#include "log.h"
#include "thk_actuator.h"
#include "group3_one_axis_probe.h"
#include "group3_probe.h"

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
    sec_wait_after_move = getValue<int>(name, "sec_wait_after_move", pt);
    number_of_measure = getValue<int>(name, "number_of_measure", pt);
    actuator_speed = getValue<int>(name, "actuator_speed", pt);

    magmesh_name = name + "_magmesh";
    std::string cmd = "./meshgen 1 " + name + " | uniq > " + magmesh_name;
    FILE *fp = popen(cmd.c_str(), "r");
    pclose(fp);

    actmesh_name = name + "_actmesh";
    cmd = "./meshgen 2 " + name + " | uniq > " + actmesh_name;
    fp = popen(cmd.c_str(), "r");
    pclose(fp);

    cmds_name = name + "_cmd";
    cmd = "./mesh2cmd " + name + "_actmesh" + " > " + cmds_name;
    fp = popen(cmd.c_str(), "r");
    pclose(fp);

    cmd = "wc -l " + name + "_cmd";
    fp = popen(cmd.c_str(), "r");
    char result[30];
    std::string str;
    while (fgets(result, sizeof(result), fp))
        str += result;
    pclose(fp);
    total_cmd_nums = std::atoi(result);

    datafile_name = name + "_data";
    logfile_name = name + "_log";
}

void Session::resume(){
    std::string cmd = "tail -n 1 datafile_name";
    FILE *fp = popen(cmd.c_str(), "r");
    char result[100];
    std::string str;
    while (fgets(result, sizeof(result), fp))
        str += result;
    pclose(fp);

    std::vector<std::string> results;
    boost::split(results, str, boost::is_space());

    int last_line = std::atoi(results.at(2).c_str());
    begin(last_line);
}

void Session::begin(){
    begin(0);
}

void Session::begin(int line_num){
    std::string line;
    std::vector<std::vector<std::string>> magmeshs;
    std::vector<std::vector<std::string>> actmeshs;
    std::vector<std::vector<std::string>> cmds;

    std::ifstream magmesh(magmesh_name);

    while(getline(magmesh, line)){
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_space());
        magmeshs.push_back(tokens);
    }

    magmesh.close();

    std::ifstream actmesh(actmesh_name);

    while(getline(actmesh, line)){
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_space());
        actmeshs.push_back(tokens);
    }

    actmesh.close();

    std::ifstream cmd(cmds_name);

    while(getline(cmd, line)){
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::is_space());
        cmds.push_back(tokens);
    }

    cmd.close();

    if(!(magmeshs.size() == actmeshs.size() && actmeshs.size() == cmds.size())){
        Log(Log::FATAL, "Mesh lines doesn't match").write();
    }

    Actuator *actuator = new ThkActuator(800,800,800);
    std::map<std::string, Actuator::ActuatorAxis> axismap;

    if(axis_order == "xyz"){
        axismap["1"] = Actuator::ACTUATOR_AXIS_X;
        axismap["2"] = Actuator::ACTUATOR_AXIS_Y;
        axismap["3"] = Actuator::ACTUATOR_AXIS_Z;
    }else if(axis_order == "xzy"){
        axismap["1"] = Actuator::ACTUATOR_AXIS_X;
        axismap["2"] = Actuator::ACTUATOR_AXIS_Z;
        axismap["3"] = Actuator::ACTUATOR_AXIS_Y;
    }else if(axis_order == "yxz"){
        axismap["1"] = Actuator::ACTUATOR_AXIS_Y;
        axismap["2"] = Actuator::ACTUATOR_AXIS_X;
        axismap["3"] = Actuator::ACTUATOR_AXIS_Z;
    }else if(axis_order == "yzx"){
        axismap["1"] = Actuator::ACTUATOR_AXIS_Y;
        axismap["2"] = Actuator::ACTUATOR_AXIS_Z;
        axismap["3"] = Actuator::ACTUATOR_AXIS_X;
    }else if(axis_order == "zxy"){
        axismap["1"] = Actuator::ACTUATOR_AXIS_Z;
        axismap["2"] = Actuator::ACTUATOR_AXIS_X;
        axismap["3"] = Actuator::ACTUATOR_AXIS_Y;
    }else if(axis_order == "zyx"){
        axismap["1"] = Actuator::ACTUATOR_AXIS_Z;
        axismap["2"] = Actuator::ACTUATOR_AXIS_Y;
        axismap["3"] = Actuator::ACTUATOR_AXIS_X;
    }

    Probe *p3 = new Group3Probe();
    Probe *p1 = new Group3OneAxisProbe();
    p3->initialize();
    p1->initialize();

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->init(Actuator::ACTUATOR_AXIS_X);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_X) + " init " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_X) + " init " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->init(Actuator::ACTUATOR_AXIS_Y);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Y) + " init " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Y) + " init " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->init(Actuator::ACTUATOR_AXIS_Z);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Z) + " init " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Z) + " init " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->resetAlarm(Actuator::ACTUATOR_AXIS_X);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_X) + " resetAlarm " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_X) + " resetAlarm " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->resetAlarm(Actuator::ACTUATOR_AXIS_Y);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Y) + " resetAlarm " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Y) + " resetAlarm " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->resetAlarm(Actuator::ACTUATOR_AXIS_Z);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Z) + " resetAlarm " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Z) + " resetAlarm " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->servoOn(Actuator::ACTUATOR_AXIS_X);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_X) + " resetAlarm " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_X) + " resetAlarm " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->servoOn(Actuator::ACTUATOR_AXIS_Y);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Y) + " resetAlarm " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Y) + " resetAlarm " + Actuator::error_toString(type)).write();
        }
    }

    for (;;) {
        Actuator::Actuator_Error_Type type = actuator->servoOn(Actuator::ACTUATOR_AXIS_Z);

        if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
            Log(Log::INFO, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Z) + " resetAlarm " + Actuator::error_toString(type)).write();
            break;
        }else{
            Log(Log::WARN, "Actuator "+ Actuator::axis_toString(Actuator::ACTUATOR_AXIS_Z) + " resetAlarm " + Actuator::error_toString(type)).write();
        }
    }

    std::ofstream data(datafile_name, std::ios::app);

    for(int i = line_num; i < cmds.size(); i++){
        std::vector<std::string> cmdtoken = cmds.at(i);
        if(cmdtoken.at(0) == "#"){
            for (;;) {
                Actuator::Actuator_Error_Type type = actuator->zero(axismap[cmdtoken.at(1)]);

                if(type == Actuator::Actuator_Error_Type::COMMAND_SUCCESS){
                    Log(Log::INFO, "Actuator "+ Actuator::axis_toString(axismap[cmdtoken.at(1)]) + " zero " + Actuator::error_toString(type));
                    break;
                }else{
                    Log(Log::FATAL, "Actuator "+ Actuator::axis_toString(axismap[cmdtoken.at(1)]) + " zero " + Actuator::error_toString(type));
                    return;
                }
            }

            sleep(sec_wait_after_move);
            continue;

        }else{
            int dist_1 = std::atoi(cmdtoken.at(0).c_str());
            int dist_2 = std::atoi(cmdtoken.at(1).c_str());
            int dist_3 = std::atoi(cmdtoken.at(2).c_str());

            Actuator::Direction dir_1 = Actuator::Direction::POSITIVE;
            Actuator::Direction dir_2 = Actuator::Direction::POSITIVE;
            Actuator::Direction dir_3 = Actuator::Direction::POSITIVE;

            if(dist_1 < 0){
                dir_1 = Actuator::Direction::NEGATIVE;
                dist_1 = std::abs(dist_1);
            }

            if(dist_2 < 0){
                dir_2 = Actuator::Direction::NEGATIVE;
                dist_2 = std::abs(dist_2);
            }

            if(dist_1 < 0){
                dir_3 = Actuator::Direction::NEGATIVE;
                dist_3 = std::abs(dist_3);
            }

            if(dist_1 != 0){
                actuator->setDistance(axismap["1"], dist_1);
                actuator->move(axismap["1"], dir_1);
                Log(Log::INFO, "Actuator " + Actuator::axis_toString(axismap["1"]) + " moved " + std::to_string(dist_1)).write();
            }
            if(dist_2 != 0){
                actuator->setDistance(axismap["2"], dist_2);
                actuator->move(axismap["2"], dir_2);
                Log(Log::INFO, "Actuator " + Actuator::axis_toString(axismap["2"]) + " moved " + std::to_string(dist_2)).write();
            }
            if(dist_3 != 0){
                actuator->setDistance(axismap["3"], dist_3);
                actuator->move(axismap["3"], dir_3);
                Log(Log::INFO, "Actuator " + Actuator::axis_toString(axismap["3"]) + " moved " + std::to_string(dist_3)).write();
            }
            sleep(sec_wait_after_move);
        }

        for(int j = 0; j < number_of_measure; j++){
            Probe::ProbeValue v1 =  p1->getValue();
            Probe::ProbeValue v3 = p3->getValue();
            time_t time = std::time(nullptr);
            char s_time[256];
            std::tm *ptm = std::localtime(&time);
            strftime(s_time, 256, "%Y-%m-%d %H:%M:%S ", ptm);

            std::vector<std::string> vec = magmeshs.at(i);
            std::string x,y,z;
            if(axis_order == "zxy"){
                z = vec.at(0);
                x = vec.at(1);
                y = vec.at(2);
            }else if(axis_order == "zyx"){
                z = vec.at(0);
                y = vec.at(1);
                x = vec.at(2);
            }else{
                Log(Log::LogLevel::FATAL, "not implemented");
                exit(EXIT_FAILURE);
            }

            double real_x, real_y, real_z;

            //TODO: Convert
            Actuator::ActuatorResponse res_x;
            Actuator::ActuatorResponse res_y;
            Actuator::ActuatorResponse res_z;

            std::string line;
            line += std::string(s_time);
            line += " " + std::to_string(i) + " ";
            line += x + " " + y + " " + z + " ";
            line += std::to_string(real_x) + " " + std::to_string(real_y) + " " + std::to_string(real_z) + " ";
            line += std::to_string(v3.x) + " " + std::to_string(v3.y) + " " + std::to_string(v3.z) + " " + std::to_string(v1.x);
            data <<  line << std::endl;
            usleep(1000 * msec_measure_time);
        }
    }
}
