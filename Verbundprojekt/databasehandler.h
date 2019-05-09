#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

//#include "initdb.h"
#include "auftrag.h"
#include "timestamp.h"

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    QSqlDatabase db;
//    QSqlQuery query;

    void InitDB();

    int GetZielStationsplatzFree(int station); //Return the Platz, when free, else 0
    bool IsStationRobotFree(int station);
    int GetLagerWerkstueck(); //return 0 if not available, else Platz 1 or 2
    QList<Prozess*> GetAllExistingProzesses();
    int GetNextFreeParkplatz();
    int GetRobotWerkstueck(int robot);
    bool IsRobotOnParkplatz(int robot);
    int GetNextLfdId();
    int GetWerkstueckOnStation(int station);
    int GetFreeLadestation();
    int GetWerkstueckPosition(int werkstuck);

    void UpdateArbeitsplatz(int robot, int werkstueck, int station);
    void UpdateRobotWerkstueck(int robot, int werkstueck);


private:
    void SendOverQuary(QSqlQuery &q, const QString &name);
    void UpdateRobotAkku(int robot, int akku);
    void UpdateRobotStatus(int robot, int status);


signals:

    void TimestampsOfStationReceived(QList<Timestamp*> t);
    void TimestampsOfWerkstueckReceived(QList<Timestamp*> t);

public slots:
    void SendAuftrag(Auftrag *A);
    void SendProzess(Prozess *P);
    void UpdateStationPlaceStatus(int id, int status);
    void UpdateRFIDWrite(int id);
    void UpdateParkplatz(int ID, int status, int roboterid);
    void UpdateWerkstueckFortschritt(int werkstueck, int fortschritt);
    void UpdateRobot1Akku(int akku);
    void UpdateRobot2Akku(int akku);
    void UpdateRobot3Akku(int akku);
    void UpdateRobot4Akku(int akku);
    void UpdateRobot1Status(int status, int pos1, int pos2);
    void UpdateRobot2Status(int status, int pos1, int pos2);
    void UpdateRobot3Status(int status, int pos1, int pos2);
    void UpdateRobot4Status(int status, int pos1, int pos2);

    void SetS8P1Free();
    void SetS8P2Free();

    void GetTimeStampsOfWerkstueck(int werkstueck);
    void GetTimeStampsOfArbeitsplatz(int arbeitsplatz);
};

#endif // DATABASEHANDLER_H
