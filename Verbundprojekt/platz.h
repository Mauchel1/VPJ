#ifndef PLATZ_H
#define PLATZ_H

#include <QObject>

class Platz : public QObject
{
    Q_OBJECT
public:
    explicit Platz(int id, QObject *parent = nullptr);
    int Status() const {return status;}
    int ID() const {return id;}
private:
    int status = 0; //frei = 0, 1 = reserviert, 2 = belegt - in Arbeit, 3 = belegt - fertig, 4 = defekt
    int id;

signals:
    void ProzessFinished();
    void PlatzChanged(int id, int newState);

public slots:
    void setFree();
    void setReserved();
    void setFull();
    void setDefect();
    void setFullReady();
};

#endif // PLATZ_H
