//
// Created by huan on 3/12/17.
//

#include "helper.h"
#include <dirent.h>
#include <iostream>
#include <algorithm>

using namespace std;

const char *testFolder = "dataset/test/";
const char *trainFolder = "dataset/train/";

vector<string> get_file_list(bool useTest) {
    vector<string> list;
    string dir_str;
    DIR *dir = NULL;
    struct dirent *entry;

    if (useTest) dir_str = testFolder;
    else dir_str = trainFolder;
    dir = opendir(dir_str.c_str());
    if (!dir) {
        cerr << "Error opening " << ((useTest) ? testFolder : trainFolder) << endl;
        exit(EXIT_FAILURE);
    }
    while (entry = readdir(dir))
        if (entry->d_type == DT_REG)
            list.push_back(dir_str + string(entry->d_name));
    sort(list.begin(), list.end());
    return list;
}

// This method assumes that there are 20 joints per frame
// PRETTY BAD ASSUMPTION, BUT IT WORKS...
jposes_of_frame get_joint_pos_of_frame(ifstream &fin) {
    jposes_of_frame result;
    int frame_id, joint_id;
    float x, y, z;

    for (int i = 0; i < 20; i++) {
        fin >> frame_id >> joint_id >> x >> y >> z;
        //cout << frame_id << "  " << joint_id << "  " << x << "  " << y << "  " << z << endl;
        result.push_back(joint_pos(x, y, z));
    }

    return result;
}

jposes_of_instance get_joint_pos_of_instance(string &filename) {
    jposes_of_instance result;
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
