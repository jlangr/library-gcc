#include "MailDestination.h"
#include "Transport.h"
#include "Endpoint.h"

#include <string>

using namespace std;

MailDestination::MailDestination(const string& address)
    : mAddress(address) {}

MailDestination::~MailDestination(void) {}

/* static */ Endpoint MailDestination::createEndpoint(const string& address) {
    throw MailDestinationException();
}

/* static */ Endpoint MailDestination::endpointForDestination(MailDestination& destination) {
    return createEndpoint(destination.address());
}

void MailDestination::send(MailMessage& message) {
    Transport::send(message);
}

string MailDestination::address() const {
    return mAddress;
}
