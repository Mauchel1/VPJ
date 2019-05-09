#ifndef PROZESS_H
#define PROZESS_H

#include <QObject>
#include <QList>
#include <QTimer>
#include "prozessschritt.h"

class Prozess : public QObject
{
    Q_OBJECT
public:
    explicit Prozess(QObject *parent = nullptr);
    QList<Prozessschritt *> Prozessschritte;
    int Fortschritt() const {return fortschritt;}
    bool InProgress() const {return inProgress;}
    bool Blocked() const {return blocked;}
    void SetBlocked(){blocked = true;}
    void StartTimer(int sek);
    int lfdId;
    int referenzId;

    Prozessschritt* GetNextUnfinishedProzessstep();
    Prozessschritt* GetActualProzessstep();
private:
    QTimer *timer;
    int fortschritt = 0;
    bool inProgress = false;
    bool blocked = false;

signals:
    void ProzessFinished(int station);
    void FortschrittUpdated();

public slots:
    void UpdateFortschritt();
    void SetProgressTrue();
    void SetProgressFalse();
    void TimerElapsed();

};

#endif // PROZESS_H
