#ifndef TIMESTAMP_SOURCE_H
#define TIMESTAMP_SOURCE_H

#include <list>
#include "boost/date_time/gregorian/gregorian_types.hpp"

class TimestampSource
{
public:
    TimestampSource(void);
    ~TimestampSource(void);

    static void clearQueue();
    static void queueNextTime(boost::gregorian::date&);
    static boost::gregorian::date now();
    static bool isExhausted();

private:
    static std::list<boost::gregorian::date> mStoredTimes;
};

#endif
