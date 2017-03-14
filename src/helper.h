//
// Created by huan on 3/12/17.
//

#ifndef SKELETON_BASED_ROBOT_REASONING_HELPER_H
#define SKELETON_BASED_ROBOT_REASONING_HELPER_H

#include <vector>
#include <string>
#include <fstream>

struct joint_pos {
    float x;
    float y;
    float z;

    joint_pos() {
        x = 0;
        y = 0;
        z = 0;
    }

    joint_pos(float tx, float ty, float tz) {
        x = tx;
        y = ty;
        z = tz;
    }
};

typedef std::vector<joint_pos> jposes_of_frame;
typedef std::vector<jposes_of_frame> jposes_of_instance;

std::vector<std::string> get_file_list(bool useTest);

jposes_of_frame get_joint_pos_of_frame(std::ifstream &fin);

jposes_of_instance get_joint_pos_of_instance(std::string &filename);

#endif //SKELETON_BASED_ROBOT_REASONING_HELPER_H
