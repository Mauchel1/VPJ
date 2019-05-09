#ifndef FERTIGUNGSPLANUNG_H
#define FERTIGUNGSPLANUNG_H

#include <QObject>
#include <QStateMachine>
#include <QRandomGenerator>
#include "robotino.h"
#include "auftrag.h"
#include "fertigungsstrasse.h"
#include "databasehandler.h"
#include "udphandler.h"


class Fertigungsplanung : public QObject
{
    Q_OBJECT
public:
    explicit Fertigungsplanung(QObject *parent = nullptr);
    QList<Auftrag*> Auftragsliste;
    QList<Prozess*> Prozessliste;
    void InitProzesses();
    void Start();

    Fertigungsstrasse Fs;

    QStateMachine StateMachine;
    QState *StateWait = new QState;
    QState *StateSendLoadingTaskWait = new QState;
    QState *StateSendPositionTaskWait = new QState;
    QState *StateSendParkingTaskWait = new QState;
    QState *StateCheckRobots = new QState;
    QState *StateCheckParkplatzRobots = new QState;
    QState *StateCheckAkku = new QState;
    QState *StateCheckAuftrag = new QState;
    QState *StateSendTimeout = new QState;
    QState *StateSendLoadingTask = new QState;
    QState *StateSendPositionTask = new QState;
    QState *StateSendParkingTask = new QState;

    Robotino *r1;
    Robotino *r2;
    Robotino *r3;
    Robotino *r4;
    UdpHandler *r1UDP;
    UdpHandler *r2UDP;
    UdpHandler *r3UDP;
    UdpHandler *r4UDP;
    DatabaseHandler *db;

    Robotino *usedRobot;
    UdpHandler *usedUDP;
    Prozessschritt *usedProzessstep;
    Prozess *usedProzess;
    QVector<double> *positionSendData = new QVector<double>;
    QTimer *timer = new QTimer();
    QTimer *sendtimer = new QTimer();
    QTimer *sendtimeout = new QTimer();

    void AddTransitionsToStates();
    void AddStatesToStateMachine();

private:
    QList<int> GetShuffeled1To4();
    void OnRobotGreiferChanged(int robotid, bool greifer);
    void OnRobotStatusChanged (int robotID, int status, int pos1, int pos2);
    bool pause = false;


signals:
    void DebugAreaString(QString message);
    void ProzessAdded(Prozess *P);
    void AuftragAdded(Auftrag *A);

    void StationChanged(int ID, bool newState);

    void nextState();
    void nextState2();
    void nextState3();

    void UpdateRobotinoPixmap(int RobotID);

    void StationClicked(int station);
    void UpdateStationToolTip(int ID, QString temp);
    void WerkstueckClicked(int werkstueck);

public slots:
    void OnStationClickedNormal(int id);
    void UpdateHardStationStatus(int id, int status);
    void UpdateHardStationsplatzStatus(int id, int status);
    void UpdateHardParkplatzStatus(int id, int status);
    void UpdateHardRobotDefect(int id, bool defect);
    void StationReady(int station);
    void RobotErrorOccured(int robotID, int error);

    void UpdatePause(bool pause);
    void AddAuftrag(QVector<int> A);
    void AddProzess(Prozess *P);
    void UpdateRobotino1Greifer(bool status);
    void UpdateRobotino2Greifer(bool status);
    void UpdateRobotino3Greifer(bool status);
    void UpdateRobotino4Greifer(bool status);
    void UpdateRobotino1Status(int status, int pos1, int pos2);
    void UpdateRobotino2Status(int status, int pos1, int pos2);
    void UpdateRobotino3Status(int status, int pos1, int pos2);
    void UpdateRobotino4Status(int status, int pos1, int pos2);

    void CheckRobots();
    void CheckParkplatzRobots();
    void CheckAkku();
    void CheckAuftrag();
    void Wait();
    void SendTimeout();
    void SendLoadingTask();
    void SendLoadingTaskWait();
    void SendPositionTask();
    void SendPositionTaskWait();
    void SendParkingTask();
    void SendParkingTaskWait();

    void DebugSlot();
};

#endif // FERTIGUNGSPLANUNG_H
