//
// Created by huan on 3/13/17.
//

#include "RAD.h"
#include <cmath>
#include <iomanip>

using namespace std;

RAD::RAD(bool flag) {
    use_test_ = flag;
    if (flag) out_file_name_ = "rad_d1.t";
    else out_file_name_ = "rad_d1";

    distances.resize(5);
    angles.resize(5);

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
    return 180*acos(cos_theta)/3.14159265358;
}


double relative_angle_respected_to_center(position &a, position &b, position &center) {
    double angle_a_to_center = angle(a, center);
    double angle_b_to_center = angle(b, center);
    return abs(angle_a_to_center - angle_b_to_center);
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

void WriteOut(vector<double> &obj) {
    ofstream fout("out.txt");
    fout << fixed << setprecision(4);
    for (double &f:obj)
        fout << f << "\t";

    fout << endl;
    fout.close();
}

void RAD::calculate() {
    // part pesudocode
    for (positions_of_instance &ins:positions_instances) { // for each instance
        distances.clear();
        angles.clear();
        distances.resize(5);
        angles.resize(5);

        double min_dist, max_dist, min_angle, max_angle;
        size_t num_frame = ins.size();
        for (positions_of_frame &frame: ins) {
            calculate_single_frame(frame);
        }
        //cout << "computed for one instance" << endl;
        //WriteOut(distances[0]);
        // TODO: compute a hist of N (hyperparam) bins for each di
        // TODO: compute a hist of M bins for each thetai
        // TODO: Determine the upper and lower bound for hist, and bin size for hist
        // Now assume N = 10, M = 9


        vector<vector<double >> Nbins = putting_N_bins(distances);
        vector<vector<double >> Mbins = putting_M_bins(angles);

        // Normalize
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

        os_buff_ << endl;
    }
}

vector<vector<double >> RAD::putting_N_bins(vector<vector<double>> &distances) {
    const static size_t num_bin = 10;
    const static double bin_range[num_bin] = {0.07, 2 * 0.07, 3 * 0.07, 4 * 0.07, 5 * 0.07, 6 * 0.07, 7 * 0.07,
                                              8 * 0.07, 9 * 0.07, 0.7};

    static double min = 10000, max = 0;     // for debug


    vector<vector<double >> result;

    for (vector<double> &a: distances) {
        vector<double> Nbin(num_bin, 0);
        for (double &data: a) {
            if (data > max)
                max = data;
            if (data < min)
                min = data;

            for (int i = 0; i < num_bin; ++i) {
                if (data < bin_range[i]) {
                    Nbin[i]+=1;
                    break;
                }
            }
        }
        result.push_back(Nbin);
    }

    cout << fixed << setprecision(2);
    cout << result.size() << endl;
    cout << "Dista: min = " << min << "\tmax = " << max << endl;

    return result;
}

std::vector<std::vector<double >> RAD::putting_M_bins(std::vector<std::vector<double>> &angles) {
    const static size_t num_bin = 9;
    const static double bin_range[num_bin] = {10, 20, 30, 40, 50, 60, 70, 80, 90};

    static double min = 10000, max = 0;     // for debug

    vector<vector<double >> result;
    for (vector<double> &a: angles) {
        vector<double> Nbin(num_bin, 0);
        for (double &data: a) {
            if (data > max)
                max = data;
            if (data < min)
                min = data;

            for (int i = 0; i < num_bin; ++i) {
                if (data < bin_range[i]) {
                    Nbin[i]+=1;
                    break;
                }
            }
        }
        result.push_back(Nbin);
    }

    cout << fixed << setprecision(2);
    cout << result.size() << endl;
    cout << "Angle: min = " << min << "\tmax = " << max << endl;

    return result;
}

