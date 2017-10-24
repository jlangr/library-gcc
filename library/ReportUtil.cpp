#include <string>
#include <sstream>

#include "ReportUtil.h"

using namespace std;

/* static */ 
string ReportUtil::transform(const string& x, int count, int spacing, StringOp op) {
    stringstream buffer;
    stringstream buffer1;
    unsigned int w = count + spacing;
    string pads;
    switch (op) {
        case StringOp::under:
            {
                for (unsigned int i = 0; i < w - spacing; i++) {
                    buffer << '-';
                }
                string ptext{buffer.str()};
                pads = "";
                buffer1 << ptext;
                unsigned int l = w - ptext.length();
                for (unsigned int j = 0; j < l; j++) {
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
