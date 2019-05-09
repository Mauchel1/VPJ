#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <QString>
#include <QDateTime>

class Timestamp
{
public:
    Timestamp(int platz, int werkstueck, unsigned int time, int status);
    int Platz() const {return platz;}
    int Werkstueck() const {return werkstueck;}
    unsigned int Time() const {return time;}
    int Status() const {return status;}
    QString TimeString();
private:
    int platz;
    int werkstueck;
    unsigned int time;
    int status;
};

#endif // TIMESTAMP_H
