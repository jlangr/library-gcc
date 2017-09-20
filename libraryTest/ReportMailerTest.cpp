#include "gmock/gmock.h"

#include "MailMessage.h"
#include "Report.h"
#include "ReportMailer.h"
#include "MailDestination.h"

#include <vector>

using namespace std;
using namespace testing;

class AReportMailer: public Test
{
public:
    virtual void SetUp()
    {
    }
};

TEST_F(AReportMailer, CanBeCreated)
{
}

