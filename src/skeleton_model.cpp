#include "skeleton_model.h"
#include <dirent.h>
#include <iostream>
#include <algorithm>

using namespace std;

skeleton_model::skeleton_model() {}

skeleton_model::~skeleton_model() {}

void skeleton_model::get_file_list() {
    string dir_str;
    DIR *dir = NULL;
    struct dirent *entry;

    // If use_test, using the testfolder, otherwise useing trainfolder.
    if (use_test_) dir_str = testFolder_;
    else dir_str = trainFolder_;

    // try to open the corresponding directory
    dir = opendir(dir_str.c_str());
    if (!dir) {
        cerr << "Error opening " << dir_str << endl;
        exit(EXIT_FAILURE);
    }

    // read all contents & sort the results
    while (entry = readdir(dir))
        if (entry->d_type == DT_REG)
            file_list_.push_back(dir_str + string(entry->d_name));
    sort(file_list_.begin(), file_list_.end());
}

void skeleton_model::load_instances() {
    cout << "Load all files" << endl;
    for (string &s : file_list_)
        positions_instances.push_back(get_joint_pos_of_instance(s));
    cout << "Finish loading " << positions_instances.size() << " instances " << endl;
}

void skeleton_model::write_to_file() {
    ofstream fout(out_file_name_);
    if (!fout) {
        cerr << "What?" << endl;
        exit(EXIT_FAILURE);
    }
    fout << os_buff_.str();
    fout.close();
}

double skeleton_model::dist_between(position &a, position &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

positions_of_instance skeleton_model::get_joint_pos_of_instance(string &filename) {
    positions_of_instance result;
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // this loop always read one more because of istream.good()
    while (fin) {
        result.push_back(get_joint_pos_of_frame(fin));
    }

    // so remove one
    result.pop_back();

    return result;
}

// This method assumes that there are 20 joints per frame
// PRETTY BAD ASSUMPTION, BUT IT WORKS...
positions_of_frame skeleton_model::get_joint_pos_of_frame(ifstream &fin) {
    positions_of_frame result;
    int frame_id, joint_id;
    float x, y, z;
    string a;
    for (int i = 0; i < 20; i++) {
        fin >> frame_id >> joint_id >> x >> y >> z;
        result[joint_id] = position(x, y, z);
    }

    return result;
}
