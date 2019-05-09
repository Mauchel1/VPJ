#include "timestamp.h"

Timestamp::Timestamp(int platz, int werkstueck, unsigned int time, int status)
{
    this->platz = platz;
    this->werkstueck = werkstueck;
    this->time = time;
    this->status = status;
}

QString Timestamp::TimeString()
{
    QDateTime timestamp;
    timestamp.setTimeSpec(Qt::LocalTime);
    timestamp.setTime_t(time);
    return timestamp.toString(Qt::SystemLocaleShortDate);
}
