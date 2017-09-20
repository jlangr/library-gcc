#ifndef ENDPOINT_VALIDATOR_H
#define ENDPOINT_VALIDATOR_H

class MailDestination;

class EndpointValidator
{
public:
    EndpointValidator(void);
    virtual ~EndpointValidator(void);

    virtual bool IsValid(MailDestination*) const;
};

#endif
