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

class RAD : public skeleton_model {
public:
    RAD(bool flag);

    void start();

private:
    void calculate_single_frame(positions_of_frame &);

    void calculate();

    std::vector<std::vector<double >> putting_N_bins(std::vector<std::vector<double>> &distances);
    std::vector<std::vector<double >> putting_M_bins(std::vector<std::vector<double>> &angles);

    std::vector<std::vector<double>> distances;
    std::vector<std::vector<double>> angles;

};

#endif //SKELETON_BASED_ROBOT_REASONING_RAD_H
