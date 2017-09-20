#ifndef MAIL_DESTINATION_H
#define MAIL_DESTINATION_H

#include "Endpoint.h"
#include "MailMessage.h"

#include <string>

class MailDestinationException: public std::exception
{
    const char* what() const throw()
    {
        return "unable to connect to LDAP server";
    }
};

class MailDestination
{
public:
    MailDestination(const std::string& address);
    ~MailDestination(void);

    static Endpoint CreateEndpoint(const std::string& address);
    static Endpoint EndpointForDestination(MailDestination& destination);
    static void Send(MailMessage&);

    std::string Address() const;

private:
    std::string mAddress;
};

#endif
