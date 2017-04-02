#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

#ifndef _SKELETON_POSITION_
#define _SKELETON_POSITION_

struct position {
    float x;
    float y;
    float z;

    position() {
        x = 0;
        y = 0;
        z = 0;
    }

    position(float tx, float ty, float tz) {
        x = tx;
        y = ty;
        z = tz;
    }
};

#endif // !_SKELETON_POSITION_

#ifndef _SKELETON_DATA_STRUCT_
#define _SKELETON_DATA_STRUCT_
typedef map<size_t, position> positions_of_frame;
typedef vector<positions_of_frame> positions_of_instance;
#endif // !_SKELETON_DATA_STRUCT_

class skeleton_model {
public:
    skeleton_model() {};

    ~skeleton_model() {};

    virtual void start() = 0;

protected:
    void get_file_list();

    void load_instances();

    void write_to_file();

    double dist_between(position &a, position &b);

    const char *testFolder_ = "dataset/test/";
    const char *trainFolder_ = "dataset/train/";

    bool use_test_;
    bool svm_output;
    string out_file_name_;
    vector<string> file_list_;
    vector<positions_of_instance> positions_instances;
    vector<string> instance_names;
    ostringstream os_buff_;

    const size_t HIP_CENTER = 1;
    const size_t SPINE = 2;
    const size_t SHOULDER_CENTER = 3;
    const size_t HEAD = 4;
    const size_t SHOULDER_LEFT = 5;
    const size_t ELBOW_LEFT = 6;
    const size_t WRIST_LEFT = 7;
    const size_t HAND_LEFT = 8;
    const size_t SHOULDER_RIGHT = 9;
    const size_t ELBOW_RIGHT = 10;
    const size_t WRIST_RIGHT = 11;
    const size_t HAND_RIGHT = 12;
    const size_t HIP_LEFT = 13;
    const size_t KNEE_LEFT = 14;
    const size_t ANKLE_LEFT = 15;
    const size_t FOOT_LEFT = 16;
    const size_t HIP_RIGHT = 17;
    const size_t KNEE_RIGHT = 18;
    const size_t ANKLE_RIGHT = 19;
    const size_t FOOT_RIGHT = 20;

private:
    positions_of_instance get_joint_pos_of_instance(string &filename);

    positions_of_frame get_joint_pos_of_frame(ifstream &fin);
};

