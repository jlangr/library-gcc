#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "MailMessage.h"

class Transport
{
public:
    Transport(void);
    ~Transport(void);

    static void send(const MailMessage&);
};

#endif
