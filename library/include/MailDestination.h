#ifndef MAIL_DESTINATION_H
#define MAIL_DESTINATION_H

#include "Endpoint.h"
#include "MailMessage.h"

#include <string>

class MailDestinationException: public std::exception {
    const char* what() const throw() {
        return "unable to connect to LDAP server";
    }
};

class MailDestination {
public:
    MailDestination(const std::string& address);
    ~MailDestination(void);

    static Endpoint createEndpoint(const std::string& address);
    static Endpoint endpointForDestination(MailDestination& destination);
    static void send(MailMessage&);

    std::string address() const;

private:
    std::string mAddress;
};

#endif
