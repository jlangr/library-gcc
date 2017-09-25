#include "gmock/gmock.h"

#include "FileReport.h"

#include <iostream>
#include <vector>

using namespace std;

TEST(AFileReport, Runs) {
    FileReport report("f.txt");

    report.load();

    cout << "1: " << report.name() << endl;
    cout << "2: >" << report.text() << "<" << endl;


    FAIL();
}
