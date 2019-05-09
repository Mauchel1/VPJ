#include "platz.h"

Platz::Platz(int id, QObject *parent) : QObject(parent)
{
    this->id = id;
}

void Platz::setFree()
{
    if (status != 0){
        status = 0;
        emit PlatzChanged(id, 0);
    }
}

void Platz::setReserved()
{
    if (status != 1){
        status = 1;
        emit PlatzChanged(id, 1);
    }
}

void Platz::setFull()
{
    if (status != 2){
        status = 2;
        emit PlatzChanged(id, 2);
    }

//    timer->start(milliseconds);
}

void Platz::setFullReady()
{
    if (status != 3){
        status = 3;
        emit PlatzChanged(id, 3);
        emit ProzessFinished();
    }

}

void Platz::setDefect()
{
    if (status != 4){
        status = 4;
        emit PlatzChanged(id, 4);
    }
}
