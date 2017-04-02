//
// Created by huan on 3/13/17.
//

#include "RAD.h"
#include <cmath>
#include <iomanip>

using namespace std;

RAD::RAD(bool flag, bool svm) {
    use_test_ = flag;
    svm_output = svm;
    if (flag) {
        if (svm) out_file_name_ = "rad_d2.t";
        else out_file_name_ = "rad_d1.t";
    } else {
        if (svm) out_file_name_ = "rad_d2";
        else out_file_name_ = "rad_d1";
    }

    get_file_list();
    load_instances();
}

void RAD::start() {
    cout << "start calculating RAD" << endl;
    os_buff_.clear();

    calculate();
    write_to_file();
}

double angle(position &a, position &b) {
    double x_dot_y = a.x * b.x + a.y * b.y + a.z * b.z;
    double x_norm = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
    double y_norm = sqrt(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2));
    double cos_theta = x_dot_y / (x_norm * y_norm);
    return 180 * acos(cos_theta) / 3.14159265358;
}

double relative_angle_respected_to_center(position &a, position &b, position &center) {
    position a_to_center, b_to_center;
    a_to_center.x = a.x - center.x;
    a_to_center.y = a.y - center.y;
    a_to_center.z = a.z - center.z;
    b_to_center.x = b.x - center.x;
    b_to_center.y = b.y - center.y;
    b_to_center.z = b.z - center.z;

    return angle(a_to_center, b_to_center);
}

/**
 * This function calculate the following things:
 * 1. compute and store the distances between body extremities to body center
 *      The order is Head, Right_hand Left_hand Right_foot Left_foot
 * 2. compute and store angles between two adjacent body extremities
 *      The order is Right_hand - Head; Head - Left_hand; Left_hand - Left_foot; Left_foot - Right_foot; Right_foot - Right_hand;
 *
 * @param frame     a single frame data
 */
void RAD::calculate_single_frame(positions_of_frame &frame) {
    distances[0].push_back(dist_between(frame[HEAD], frame[HIP_CENTER]));
    distances[1].push_back(dist_between(frame[HAND_RIGHT], frame[HIP_CENTER]));
    distances[2].push_back(dist_between(frame[HAND_LEFT], frame[HIP_CENTER]));
    distances[3].push_back(dist_between(frame[FOOT_RIGHT], frame[HIP_CENTER]));
    distances[4].push_back(dist_between(frame[FOOT_LEFT], frame[HIP_CENTER]));
    angles[0].push_back(relative_angle_respected_to_center(frame[HAND_RIGHT], frame[HEAD], frame[HIP_CENTER]));
    angles[1].push_back(relative_angle_respected_to_center(frame[HEAD], frame[HAND_LEFT], frame[HIP_CENTER]));
    angles[2].push_back(relative_angle_respected_to_center(frame[HAND_LEFT], frame[FOOT_LEFT], frame[HIP_CENTER]));
    angles[3].push_back(relative_angle_respected_to_center(frame[FOOT_LEFT], frame[FOOT_RIGHT], frame[HIP_CENTER]));
    angles[4].push_back(relative_angle_respected_to_center(frame[FOOT_RIGHT], frame[HAND_RIGHT], frame[HIP_CENTER]));
}

void RAD::calculate() {
    //for (positions_of_instance &ins:positions_instances) { // for each instance
    for (size_t i = 0; i < positions_instances.size(); i++) {
        positions_of_instance &ins = positions_instances[i];
        distances.clear();
        angles.clear();
        distances.resize(5);
        angles.resize(5);

        size_t num_frame = ins.size();
        for (positions_of_frame &frame: ins) {
            calculate_single_frame(frame);
        }

        vector<vector<double >> Nbins = putting_N_bins(distances);
        vector<vector<double >> Mbins = putting_M_bins(angles);

        // Normalize
        if (svm_output) {
            int idx = 1;
            string &filename = instance_names[i];
            size_t pos_of_file = filename.find_last_of('/');
            os_buff_ << filename.substr(pos_of_file + 2, 2) << " ";
            for (vector<double> &oneBin: Nbins)
                for (double &one: oneBin) {
                    one /= num_frame;
                    os_buff_ << idx++ << ":" << one << " ";
                }
            for (vector<double> &oneBin: Mbins)
                for (double &one: oneBin) {
                    one /= num_frame;
                    os_buff_ << idx++ << ":" << one << " ";
                }
        } else {
            for (vector<double> &oneBin: Nbins)
                for (double &one: oneBin) {
                    one /= num_frame;
                    os_buff_ << one << " ";
                }


            for (vector<double> &oneBin: Mbins)
                for (double &one: oneBin) {
                    one /= num_frame;
                    os_buff_ << one << " ";
                }
        }

        os_buff_ << endl;
    }
}

vector<vector<double >> RAD::putting_N_bins(vector<vector<double>> &distances) {
    const static size_t num_bin = 15;
    const static double bin_range[num_bin] = {0.3, 0.6, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.8, 2.0, 2.3, 5};

    vector<vector<double >> result;

    for (vector<double> &a: distances) {
        vector<double> Nbin(num_bin, 0);
        for (double &data: a) {
            for (int i = 0; i < num_bin; ++i) {
                if (data < bin_range[i]) {
                    Nbin[i] += 1;
                    break;
                }
            }
        }
        result.push_back(Nbin);
    }

    return result;
}

std::vector<std::vector<double >> RAD::putting_M_bins(std::vector<std::vector<double>> &angles) {
    const static size_t num_bin = 18;
    const static double bin_range[num_bin] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160,
                                              170, 180};

    vector<vector<double>> result;

    for (vector<double> &a: angles) {
        vector<double> Nbin(num_bin, 0);
        for (double &data: a) {
            for (int i = 0; i < num_bin; ++i) {
                if (data < bin_range[i]) {
                    Nbin[i] += 1;
                    break;
                }
            }
        }
        result.push_back(Nbin);
    }

    return result;
}

