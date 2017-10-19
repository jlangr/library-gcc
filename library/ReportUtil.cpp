#include <string>
#include <sstream>

#include "ReportUtil.h"

using namespace std;

/* static */ 
string ReportUtil::transform(const string& x, int count, int spacing, StringOp op) {
    stringstream buffer;
    stringstream buffer1;
    auto w = count + spacing;
    string pads;
    switch (op) {
        case StringOp::under:
            {
                for (auto i = 0; i < w - spacing; i++) {
                    buffer << '-';
                }
                string ptext{buffer.str()};
                pads = "";
                buffer1 << ptext;
                auto l = w - ptext.length();
                for (auto j = 0; j < l; j++) {
                    pads += " ";
                }
                buffer1 << pads;
            }
            break;
        case StringOp::pad:
            {
                pads = " ";
                auto l = spacing;
                while (l > 1) {
                    pads = pads + " ";
                    l = l - 1;
                }
                buffer << x;
                buffer << pads;
                buffer1 << buffer.str();
            }
            break;
    }
    return buffer1.str();
}
