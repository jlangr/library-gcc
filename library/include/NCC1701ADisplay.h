#ifndef NCC1701A_DISPLAY_H
#define NCC1701A_DISPLAY_H

#include "DisplayListener.h"

#include <string>

using namespace std;

class NCC1701ADisplay: public DisplayListener {
public:
    NCC1701ADisplay() {}
    virtual ~NCC1701ADisplay() {}

    virtual void showMessage(const std::string& text) {}
};

#endif
