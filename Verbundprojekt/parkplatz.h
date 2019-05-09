#ifndef PARKPLATZ_H
#define PARKPLATZ_H

#include <QObject>

class Parkplatz : public QObject
{
    Q_OBJECT
public:
    explicit Parkplatz(int id, QObject *parent = nullptr);
    int Status() const {return status;}
    int ID() const {return id;}
private:
    int status = 0; //frei = 0, 1 = reserviert, 2 = belegt
    int id;

signals:
    void PlatzChanged(int id, int newState);

public slots:
    void setReserved();
    void setFree();
    void setFull();
};

#endif // PARKPLATZ_H
