#ifndef AUFTRAG_H
#define AUFTRAG_H

#include <QObject>
#include <QList>
#include "prozess.h"

class Auftrag : public QObject
{
    Q_OBJECT
public:
    explicit Auftrag(QObject *parent = nullptr);
    QList<Prozess*> Prozesse;
    int fortschritt = 0;
    int id = 1;

    QList<Prozessschritt *> GetNextUnfinishedProzesssteps();
    QList<Prozess *> GetAllUnfinishedProzesses();
    Prozess* GetProzessByID(int ID);

signals:

    void FortschrittUpdated();

public slots:
    void UpdateFortschritt();
};

#endif // AUFTRAG_H
