#ifndef REPORT_UTIL_H
#define REPORT_UTIL_H

#include <string>

enum class StringOp : int { pad = 0, under = 1 };

class ReportUtil {
public: 
    static std::string transform(const std::string& x, int count, int spacing, StringOp op);
};
#endif
