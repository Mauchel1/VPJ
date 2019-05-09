#ifndef FERTIGUNGSSTRASSE_H
#define FERTIGUNGSSTRASSE_H

#include "station.h"
#include "parkplatz.h"

class Fertigungsstrasse
{
public:
    Fertigungsstrasse();
    Station S1;
    Station S2;
    Station S3;
    Station S4;
    Station S5;
    Station S6;
    Station S7;
    Station S8;
    Parkplatz P1;
    Parkplatz P2;
    Parkplatz P3;
    Parkplatz P4;
    Parkplatz L1;
    Parkplatz L2;

    Platz* GetStationPlatzByID(int id);
    Parkplatz* GetPlatzByID(int id);
};

#endif // FERTIGUNGSSTRASSE_H
