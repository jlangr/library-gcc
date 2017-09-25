#include "TimestampSource.h"
#include <list>

using namespace boost::gregorian;
using namespace std;

list<date> TimestampSource::mStoredTimes;

TimestampSource::TimestampSource(void)
{
}

TimestampSource::~TimestampSource(void)
{
}

void TimestampSource::clearQueue()
{
    mStoredTimes.clear();
}

void TimestampSource::queueNextTime(date& time)
{
    mStoredTimes.push_back(time);
}

date TimestampSource::now()
{
    if (isExhausted())
    {
        return date(day_clock::local_day());
    }
    date firstStored = mStoredTimes.front();
    mStoredTimes.pop_front();
    return firstStored;
}

bool TimestampSource::isExhausted()
{
    return mStoredTimes.empty();
}
