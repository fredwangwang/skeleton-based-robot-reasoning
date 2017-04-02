//
// Created by huan on 3/20/17.
//

#ifndef SKELETON_BASED_ROBOT_REASONING_HJPD_H
#define SKELETON_BASED_ROBOT_REASONING_HJPD_H

#include "skeleton_model.h"

class HJPD : public skeleton_model {
public:
    HJPD(bool flag, bool svm);

    void start();

private:
    void calculate();
    void calc_relative_displacement_to_center(positions_of_frame &frame);
    void calc_single_relative_displacement_to_center(positions_of_frame &frame, size_t posi);

    vector<vector<double>> relative_x_distances;
    vector<vector<double>> relative_y_distances;
    vector<vector<double>> relative_z_distances;
};


#endif //SKELETON_BASED_ROBOT_REASONING_HJPD_H
