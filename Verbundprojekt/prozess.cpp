#include "prozess.h"

Prozess::Prozess(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    //Prozessschritte.empty();
    QObject::connect(timer, &QTimer::timeout, this, &Prozess::TimerElapsed);
}

void Prozess::UpdateFortschritt()
{
    fortschritt = 0;
    foreach(Prozessschritt *item, Prozessschritte)
    {
        if(item->Fortschritt())
        {
            fortschritt += 100/(Prozessschritte.size()+0);
        }
    }
    //try catch round errors and get always to 100 if prozess finished
    if (fortschritt > 95)
    {
        fortschritt = 100;
    }
    emit FortschrittUpdated();
}

Prozessschritt* Prozess::GetNextUnfinishedProzessstep()
{
    if (fortschritt == 100)
    {
        return nullptr;
    }
    foreach (Prozessschritt *item, Prozessschritte)
    {
        if (!item->Fortschritt())
        {
            return item;
        }
    }
    return nullptr;
}

Prozessschritt* Prozess::GetActualProzessstep()
{
    if (fortschritt == 100)
    {
        return Prozessschritte.last();
    }
    else if (fortschritt == 0)
    {
        return nullptr;
    }
    for (int i = 1; i < Prozessschritte.length(); i++)
    {
        if (!Prozessschritte.at(i)->Fortschritt())
        {
            return Prozessschritte.at(i-1);
        }
    }
    return nullptr;
}


void Prozess::SetProgressFalse()
{
    inProgress = false;
}

void Prozess::SetProgressTrue()
{
    inProgress = true;
}

void Prozess::StartTimer(int sek)
{
    timer->setSingleShot(true);
    timer->start(sek * 1000);
}

void Prozess::TimerElapsed()
{
    GetNextUnfinishedProzessstep()->SetFortschrittReady();
    emit ProzessFinished(lfdId);
    SetProgressFalse();
}



