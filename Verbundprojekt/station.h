#ifndef STATION_H
#define STATION_H

#include <QObject>
#include "platz.h"

class Station
{
public:
    Station(int id);
    Platz P1;
    Platz P2;
private:
    int ID;
};

#endif // STATION_H
