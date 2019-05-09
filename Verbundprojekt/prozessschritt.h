#ifndef PROZESSSCHRITT_H
#define PROZESSSCHRITT_H

#include <QObject>

class Prozessschritt : public QObject
{
    Q_OBJECT
public:
    explicit Prozessschritt(int station, int dauer, QObject *parent = nullptr);
    int Station() const {return station;}
    int Dauer() const {return prozessdauer;}
    bool Fortschritt() const {return fortschritt;}

    void SetFortschrittReady();

private:
    int station;
    int prozessdauer;
    bool fortschritt = false;


signals:

    void FortschrittUpdated();

public slots:

    void SetFortschrittTrue();
    void SetFortschrittFalse();
};

#endif // PROZESSSCHRITT_H
