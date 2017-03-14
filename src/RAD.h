//
// Created by huan on 3/13/17.
//

#ifndef SKELETON_BASED_ROBOT_REASONING_RAD_H
#define SKELETON_BASED_ROBOT_REASONING_RAD_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class RAD {
public:
    RAD(std::vector<std::string>, bool);

    void start();
private:
    std::vector<std::string> file_list;
    std::string out_file_name;
    std::ostringstream os_buff;
};


#endif //SKELETON_BASED_ROBOT_REASONING_RAD_H
