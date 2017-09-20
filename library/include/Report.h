#ifndef REPORT_H
#define REPORT_H

#include <string>

class Report
{
public:
    virtual ~Report(void) {}

    virtual std::string Text() const=0;
    virtual std::string Name() const=0;
};

#endif
