#include "MailMessage.h"

#include <string>

using namespace std;

MailMessage::MailMessage(const std::string& subject,
    const std::string& content,
    const std::string& from)
    : mSubject(subject)
    , mContent(content)
    , mFrom(from)
{
}

MailMessage::~MailMessage(void)
{
}

void MailMessage::addRecipient(const std::string& to)
{
    mTo.push_back(to);
}

string MailMessage::subject() const
{
    return mSubject;
}

string MailMessage::content() const
{
    return mContent;
}

vector<string> MailMessage::to() const
{
    return mTo;
}

string MailMessage::from() const
{
    return mFrom;
}
