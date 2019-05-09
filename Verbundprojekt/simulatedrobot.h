#ifndef SIMULATEDROBOT_H
#define SIMULATEDROBOT_H

#include <QObject>
#include <QStateMachine>
#include <QTimer>
#include <QVector>


class SimulatedRobot : public QObject
{
    Q_OBJECT
public:
    explicit SimulatedRobot(QObject *parent = nullptr);
    void Start();

    QStateMachine StateMachine;
    QState *State1 = new QState;
    QState *State1W = new QState;
    QState *State2 = new QState;
    QState *State3 = new QState;
    QState *State4 = new QState;
    QState *State5 = new QState;
    QState *State6 = new QState;
    QState *State7 = new QState;
    QState *State8 = new QState;
    QState *State9 = new QState;
    QState *State9W = new QState;
    QState *State10 = new QState;
    QState *State11 = new QState;

    QTimer *timer = new QTimer();
    QTimer *restarttimer = new QTimer();
    int auftragsart = 0;
    int pos1 = 0;
    int pos2 = 0;

private:
    void reset();
    void SendStatus(int status, int greifer);
    bool done = false;

signals:
    void nextState();
    void nextState2();
    void nextState3();
    void nextState4();

    void StatusDataSimulatedReceived(QVector<int> values);

public slots:

    void S1();
    void S1W();
    void S2();
    void S3();
    void S4();
    void S5();
    void S6();
    void S7();
    void S8();
    void S9();
    void S9W();
    void S10();
    void S11();

};

#endif // SIMULATEDROBOT_H
