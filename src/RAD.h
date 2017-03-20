//
// Created by huan on 3/13/17.
//

#ifndef SKELETON_BASED_ROBOT_REASONING_RAD_H
#define SKELETON_BASED_ROBOT_REASONING_RAD_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "skeleton_model.h"

using namespace std;

// TO CREATE A STAR REPRESENTATION
// THERE ARE 5 POINTS REQUIRED, THEY ARE (OFF BY ONE MODIFIED):
// CENTER:      0
// HEAD:        3
// RIGHT HAND:  7
// LEFT HAND:   11
// RIGHT FOOT:  15
// LEFT FOOT:   19

class RAD : public skeleton_model {
public:
    RAD(bool flag);

    void start();

private:
    void calculate_single_frame(positions_of_frame &);

    void calculate();

    void write_to_file();

    std::vector<std::vector<double >> putting_N_bins(std::vector<std::vector<double>> &distances);
    std::vector<std::vector<double >> putting_M_bins(std::vector<std::vector<double>> &angles);

    std::ostringstream os_buff;

    std::vector<std::vector<double>> distances;
    std::vector<std::vector<double>> angles;

};


#endif //SKELETON_BASED_ROBOT_REASONING_RAD_H
