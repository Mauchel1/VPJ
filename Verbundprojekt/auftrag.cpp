#include "auftrag.h"

Auftrag::Auftrag(QObject *parent) : QObject(parent)
{

}

void Auftrag::UpdateFortschritt()
{
    fortschritt = 0;
    foreach(Prozess *item, Prozesse)
    {
        fortschritt += item->Fortschritt();
    }
    fortschritt = fortschritt / Prozesse.size();
    if (fortschritt > 100)
    {
        fortschritt = 100;
    }
    emit FortschrittUpdated();
}

QList<Prozessschritt *> Auftrag::GetNextUnfinishedProzesssteps()
{
    QList<Prozessschritt *> unfinishedList;

    foreach (Prozess *item, Prozesse)
    {
        if (item->GetNextUnfinishedProzessstep() != nullptr)
        {
            unfinishedList.append(item->GetNextUnfinishedProzessstep());
        }
    }
    return unfinishedList;
}

Prozess * Auftrag::GetProzessByID(int id)
{
    foreach (Prozess *item, Prozesse)
    {
        if (item->lfdId == id)
        {
            return item;
        }
    }
    return nullptr;
}

QList<Prozess *> Auftrag::GetAllUnfinishedProzesses()
{
    QList<Prozess *> unfinishedList;

    foreach (Prozess *item, Prozesse)
    {
        if (item->GetNextUnfinishedProzessstep() != nullptr && item->Fortschritt() < 100 && !item->Blocked())
        {
            unfinishedList.append(item);
        }
    }
    return unfinishedList;
}
