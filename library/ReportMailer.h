#ifndef REPORT_MAILER_H
#define REPORT_MAILER_H

#include "MailMessage.h"
#include "MailDestination.h"
#include "Transport.h"
#include "Report.h"
#include "EndpointValidator.h"

#include <vector>
#include <exception>

class ReportMailerException: public std::exception
{
public:
    ReportMailerException(const std::string& message)
        : mMessage(message)
    {
    }

    virtual ~ReportMailerException() {}

    const char* what() const throw()
    {
        return mMessage.c_str();
    }

private:
    std::string mMessage;
};

class ReportMailer
{
public:
    ReportMailer(std::vector<MailDestination> destinations)
        : mDestinations(destinations)
    {
        if (mDestinations.empty())
        {
            throw ReportMailerException("destinations required");
        }
        EndpointValidator validator;
        for (std::vector<MailDestination>::iterator it = mDestinations.begin();
            it != mDestinations.end();
            it++)
        {
            MailDestination destination = *it;
            // verify all endpoints
            if (!validator.IsValid(&destination))
            {
                throw ReportMailerException("invalid endpoint");
            }
        }
    }

    virtual ~ReportMailer() 
    {
    }

    void MailReport(Report* report) 
    {
        for (std::vector<MailDestination>::iterator it = mDestinations.begin();
            it != mDestinations.end();
            it++)
        {
            MailDestination destination = *it;
            std::string toAddress = destination.Address();
            MailMessage message = ConstructMailMessage(toAddress, report);
            MailDestination::Send(message);
        }
    }

    MailMessage ConstructMailMessage(const std::string& toAddress, Report* report) const
    {
        std::string content = report->Text();
        std::string subject = report->Name();

        MailMessage message(
            subject, 
            content, 
            "Joe@example.com");

        message.AddRecipient(toAddress);

        return message;
    }

private:
    std::vector<MailDestination> mDestinations;
};

#endif
