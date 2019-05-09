#include "prozessschritt.h"

Prozessschritt::Prozessschritt(int station, int dauer, QObject *parent) : QObject(parent)
{
    this->station = station;
    this->prozessdauer = dauer;
}

void Prozessschritt::SetFortschrittReady()
{
    fortschritt = true;
    emit FortschrittUpdated();
}

void Prozessschritt::SetFortschrittTrue()
{
    fortschritt = true;
}

void Prozessschritt::SetFortschrittFalse()
{
    fortschritt = false;
}
