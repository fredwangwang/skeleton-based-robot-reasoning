//
// Created by huan on 3/13/17.
//

#include "RAD.h"
#include <cmath>

using namespace std;

RAD::RAD(vector<string> file_list, bool useTest) {
    this->file_list = file_list;
    if (useTest) out_file_name = "rad_d1.t";
    else out_file_name = "rad_d1";

    distances.resize(5);
    angles.resize(5);
}

void RAD::start() {
    load_instances();
}

void RAD::load_instances() {
    cout << "Load all files" << endl;
    for (string &s: file_list) {
        jposes_instances.push_back(get_joint_pos_of_instance(s));
    }
    cout << "Finish loading " << jposes_instances.size() << " instances " << endl;
}

double dist(joint_pos &a, joint_pos &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

double angle(joint_pos &a, joint_pos &b) {
    double x_dot_y = a.x * b.x + a.y * b.y + a.z * b.z;
    double x_norm = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
    double y_norm = sqrt(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2));
    double cos_theta = x_dot_y / (x_norm * y_norm);
    return acos(cos_theta);
}

/**
 * This function calculate the following things:
 * 1. compute and store the distances between body extremities to body center
 * 2. compute and store angles between two adjacent body extremities
 *
 * @param frame     a single frame data
 */
void RAD::calculate_single_frame(jposes_of_frame &frame) {
    distances[0].push_back(dist(frame[HEAD], frame[CENTER]));
    distances[1].push_back(dist(frame[RIGHT_HAND], frame[CENTER]));
    distances[2].push_back(dist(frame[LEFT_HAND], frame[CENTER]));
    distances[3].push_back(dist(frame[RIGHT_FOOT], frame[CENTER]));
    distances[4].push_back(dist(frame[LEFT_FOOT], frame[CENTER]));
    // TODO: add angles
}

void RAD::calculate() {
    distances.clear();
    angles.clear();
    distances.resize(5);
    angles.resize(5);
    // part pesudocode
    for (jposes_of_instance &ins:jposes_instances) { // for each instance
        for (jposes_of_frame &frame: ins) { ;
        }
        // TODO: compute a hist of N (hyperparam) bins for each di
    }

}