//
// Created by huan on 3/12/17.
//

#include <iostream>
#include "RAD.h"
#include "HJPD.h"

using namespace std;

bool useTest = false;

void print_usage() {
    cout << "Usage:" << endl
         << "program option model [SVM FORMAT]" << endl
         << "\tOption:" << endl
         << "\ttest\tusing test dataset" << endl
         << "\ttrain\tusing train dataset" << endl
         << "\tModel:" << endl
         << "\trad\tusing RAD model" << endl
         << "\thjpd\tusing HJPD model" << endl
         << "\tSVM FORMAT: " << endl
         << "\ttrue\toutput svm data format" << endl
         << "\tfalse\toutput normal data format [default]" << endl;
}

int main(int argc, char **argv) {
    skeleton_model *model;

    // parse flag and print out usage"
    if (argc < 2) {
        print_usage();
        exit(EXIT_FAILURE);
    }
    string flag(argv[1]);
    if (flag.find("test") != string::npos || flag.find("Test") != string::npos)
        useTest = true;
    else if (flag.find("train") != string::npos || flag.find("Train") != string::npos)
        useTest = false;
    else {
        cerr << "Unrecognized flag " << argv[1] << endl;
        print_usage();
        exit(EXIT_FAILURE);
    };

    string m;
    bool svm = false;
    if (argc == 4) {
        m = argv[3];
        if (m.find("t") != string::npos || m.find("T") != string::npos)
            svm = true;
    }

    if (argc >= 3) {
        m = (argv[2]);
    } else {
        cout << "Which model? (rad / hjpd): ";
        cin >> m;
    }
    if (m.find("rad") != string::npos || m.find("RAD") != string::npos)
        model = new RAD(useTest, svm);
    else if (m.find("hjpd") != string::npos || m.find("HJPD") != string::npos)
        model = new HJPD(useTest, svm);
    else {
        cerr << "Unrecognized model " << argv[2] << endl;
        print_usage();
        exit(EXIT_FAILURE);
    };

    model->start();

}