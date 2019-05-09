#include "parkplatz.h"

Parkplatz::Parkplatz(int id, QObject *parent) : QObject(parent)
{
    this->id = id;
}

void Parkplatz::setFree()
{
    status = 0;
    emit PlatzChanged(id, 0);
}

void Parkplatz::setReserved()
{
    status = 1;
    emit PlatzChanged(id, 1);
}

void Parkplatz::setFull()
{
    status = 2;
    emit PlatzChanged(id, 2);
}
