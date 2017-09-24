#ifndef MAIL_MESSAGE_H
#define MAIL_MESSAGE_H

#include <string>
#include <vector>

class MailMessage
{
public:
    MailMessage(const std::string& subject, const std::string& content, const std::string& from);
    ~MailMessage(void);

    void addRecipient(const std::string& toAddress);
    std::string subject() const;
    std::string content() const;
    std::vector<std::string> to() const;
    std::string from() const;

private:
    std::string mSubject;
    std::string mContent;
    std::vector<std::string> mTo;
    std::string mFrom;
};

#endif
