//
// Created by huan on 3/12/17.
//

#include <iostream>
#include <cmath>
#include "helper.h"
#include "RAD.h"

using namespace std;

bool useTest = false;

void print_usage() {
    cout << "Usage:" << endl
         << "program option" << endl
         << "\tOption:" << endl
         << "\t-test\tusing test dataset" << endl
         << "\t-train\tusing train dataset" << endl;
}

int main(int argc, char **argv) {
    // parse flag and print out usage"
    if (argc != 2) {
        print_usage();
        exit(EXIT_FAILURE);
    }
    string flag(argv[1]);
    if (flag.find("test") != string::npos || flag.find("Test") != string::npos) {
        useTest = true;
    } else if (flag.find("train") != string::npos || flag.find("Train") != string::npos) {
        useTest = false;
    } else {
        cerr << "Unrecognized flag " << argv[1] << endl;
        print_usage();
        exit(EXIT_FAILURE);
    };

    vector<string> ls = get_file_list(useTest);
    RAD rad(ls, useTest);
    rad.start();

//    cout << atan2(1,1)*180/3.141592653<<endl;
//    cout << atan2(1,-1)*180/3.141592653<<endl;
//    cout << atan2(-1,-1)*180/3.141592653<<endl;
//    cout << atan2(-1,1)*180/3.141592653<<endl;

}