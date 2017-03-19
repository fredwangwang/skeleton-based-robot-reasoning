#pragma once

#include <vector>
#include <string>
#include <fstream>

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

typedef std::vector<position> positions_of_frame;
typedef std::vector<positions_of_frame> positions_of_instance;

class skeleton_model
{
public:
    skeleton_model();
    ~skeleton_model();

    void set_flag(bool flag);

    virtual void start() = 0;

protected:
    void get_file_list();
    void load_instances();

    const char *testFolder_ = "dataset/test/";
    const char *trainFolder_ = "dataset/train/";

    bool use_test_;
    string out_file_name;
    vector<string> file_list_;
    vector<positions_of_instance> positions_instances;

private:
    positions_of_instance get_joint_pos_of_instance(string &filename);
    positions_of_frame get_joint_pos_of_frame(ifstream &fin);
};

