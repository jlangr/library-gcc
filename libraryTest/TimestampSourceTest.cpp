#include "gmock/gmock.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

#include "TimestampSource.h"

using namespace testing;
using namespace boost::gregorian;

class TimestampSourceTest: public Test
{
public:
    static date NEW_YEARS_DAY;
    static date GROUNDHOG_DAY;

    virtual void SetUp() 
    {
        TimestampSource::clearQueue();
    }
    virtual void TearDown() {}
};

date TimestampSourceTest::NEW_YEARS_DAY(2013, Jan, 1);
date TimestampSourceTest::GROUNDHOG_DAY(2013, Feb, 2);

TEST_F(TimestampSourceTest, RetrievesSinglePushedTime)
{
    TimestampSource::queueNextTime(NEW_YEARS_DAY);

    ASSERT_THAT(TimestampSource::now(), Eq(NEW_YEARS_DAY));
}

TEST_F(TimestampSourceTest, RetrievesMultiplePushedTimes)
{
    TimestampSource::queueNextTime(NEW_YEARS_DAY);
    TimestampSource::queueNextTime(GROUNDHOG_DAY);

    ASSERT_THAT(TimestampSource::now(), Eq(NEW_YEARS_DAY));
    ASSERT_THAT(TimestampSource::now(), Eq(GROUNDHOG_DAY));
}

TEST_F(TimestampSourceTest, IsExhaustedWhenNoTimeQueued)
{
    ASSERT_THAT(TimestampSource::isExhausted(), Eq(true));
}

TEST_F(TimestampSourceTest, IsNotExhaustedWhenTimeQueued)
{
    TimestampSource::queueNextTime(NEW_YEARS_DAY);

    ASSERT_THAT(TimestampSource::isExhausted(), Eq(false));
}

TEST_F(TimestampSourceTest, ClearExhaustsQueue)
{
    TimestampSource::queueNextTime(NEW_YEARS_DAY);

    TimestampSource::clearQueue();

    ASSERT_THAT(TimestampSource::isExhausted(), Eq(true));
}

TEST_F(TimestampSourceTest, ReturnsCurrentTimeWhenQueueExhausted)
{    
    date today(day_clock::local_day());
    TimestampSource::queueNextTime(GROUNDHOG_DAY);
    TimestampSource::now();

    date retrieved = TimestampSource::now();

    ASSERT_THAT(retrieved, Eq(today));
}
