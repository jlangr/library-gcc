#ifndef REPORT_H
#define REPORT_H

#include <string>

class Report {
public:
    virtual ~Report(void) {}

    virtual std::string text() const=0;
    virtual std::string name() const=0;
};

#endif
