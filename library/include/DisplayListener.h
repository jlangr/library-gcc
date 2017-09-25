#ifndef DISPLAY_LISTENER_H
#define DISPLAY_LISTENER_H

#include <string>

class DisplayListener
{
public:
    virtual void showMessage(const std::string& text)=0;
};

#endif
