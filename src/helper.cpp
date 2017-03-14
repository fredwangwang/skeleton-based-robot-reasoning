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

jposes_of_frame get_joint_pos_of_frame(ifstream &fin) {
    jposes_of_frame result;
    int cur_frame = fin.peek();
    int frame, joint;
    float x, y, z;
    while (fin.peek() == cur_frame) {
        fin >> frame >> joint;
        fin >> x >> y >> z;
        if (fin.good()) {
            cout << "x, y, x: " << x << "\t" << y << "\t" << z << endl;
            result.push_back(joint_pos(x, y, z));
        } else break;
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
    while (!fin.eof()) {
        result.push_back(get_joint_pos_of_frame(fin));
    }
    return result;
}
