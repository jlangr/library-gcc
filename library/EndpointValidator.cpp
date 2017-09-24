#include "EndpointValidator.h"
#include "MailDestination.h"

EndpointValidator::EndpointValidator(void)
{
}

EndpointValidator::~EndpointValidator(void)
{
}

bool EndpointValidator::isValid(MailDestination*) const
{
    return false;
}
