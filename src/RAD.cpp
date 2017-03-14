//
// Created by huan on 3/13/17.
//

#include "RAD.h"

using namespace std;

RAD::RAD(vector<string> file_list, bool useTest) {
    this->file_list = file_list;
    if (useTest) out_file_name = "rad d1.t";
    else out_file_name = "rad_d1";
}

void RAD::start() {
    for (string &s: file_list){

    }
}