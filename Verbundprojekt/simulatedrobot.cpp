#include "simulatedrobot.h"

SimulatedRobot::SimulatedRobot(QObject *parent) : QObject(parent)
{

    State1->addTransition(this, SIGNAL(nextState()), State10);
    State1->addTransition(this, SIGNAL(nextState2()), State2);
    State1->addTransition(this, SIGNAL(nextState3()), State8);
    State1->addTransition(this, SIGNAL(nextState4()), State1W);
    State1W->addTransition(timer, SIGNAL(timeout()), State1);
    State2->addTransition(timer, SIGNAL(timeout()), State3);
    State3->addTransition(timer, SIGNAL(timeout()), State4);
    State4->addTransition(timer, SIGNAL(timeout()), State5);
    State5->addTransition(timer, SIGNAL(timeout()), State6);
    State6->addTransition(timer, SIGNAL(timeout()), State7);
    State7->addTransition(timer, SIGNAL(timeout()), State1);
    State8->addTransition(timer, SIGNAL(timeout()), State9);
    State9->addTransition(this, SIGNAL(nextState()), State2);
    State9->addTransition(this, SIGNAL(nextState2()), State10);
    State9->addTransition(this, SIGNAL(nextState4()), State9W);
    State9W->addTransition(timer, SIGNAL(timeout()), State9);
    State10->addTransition(timer, SIGNAL(timeout()), State11);
    State11->addTransition(timer, SIGNAL(timeout()), State1);

    StateMachine.addState(State1);
    StateMachine.addState(State1W);
    StateMachine.addState(State2);
    StateMachine.addState(State3);
    StateMachine.addState(State4);
    StateMachine.addState(State5);
    StateMachine.addState(State6);
    StateMachine.addState(State7);
    StateMachine.addState(State8);
    StateMachine.addState(State9);
    StateMachine.addState(State9W);
    StateMachine.addState(State10);
    StateMachine.addState(State11);

    QObject::connect(State1, &QState::entered, this, &SimulatedRobot::S1);
    QObject::connect(State1W, &QState::entered, this, &SimulatedRobot::S1W);
    QObject::connect(State2, &QState::entered, this, &SimulatedRobot::S2);
    QObject::connect(State3, &QState::entered, this, &SimulatedRobot::S3);
    QObject::connect(State4, &QState::entered, this, &SimulatedRobot::S4);
    QObject::connect(State5, &QState::entered, this, &SimulatedRobot::S5);
    QObject::connect(State6, &QState::entered, this, &SimulatedRobot::S6);
    QObject::connect(State7, &QState::entered, this, &SimulatedRobot::S7);
    QObject::connect(State8, &QState::entered, this, &SimulatedRobot::S8);
    QObject::connect(State9, &QState::entered, this, &SimulatedRobot::S9);
    QObject::connect(State9W, &QState::entered, this, &SimulatedRobot::S9W);
    QObject::connect(State10, &QState::entered, this, &SimulatedRobot::S10);
    QObject::connect(State11, &QState::entered, this, &SimulatedRobot::S11);

}

void SimulatedRobot::Start()
{
    StateMachine.setInitialState(State1);
    StateMachine.start();
}

void SimulatedRobot::reset(){
    auftragsart = 0;
    pos1 = 0;
    pos2 = 0;
}

void SimulatedRobot::SendStatus(int status, int greifer){
    QVector<int> vektor(9);
    vektor[0] = 1 ;
    vektor[1] = 55 ;
    vektor[2] = 0 ;
    vektor[3] = 0 ;
    vektor[4] = 0 ;
    vektor[5] = status ;
    vektor[6] = greifer ;
    vektor[7] = 0 ;
    vektor[8] = 0 ;
    emit StatusDataSimulatedReceived(vektor);
}

void SimulatedRobot::S1()
{
    if (!done)
    {
        done = true;
        SendStatus(0,0);
    }
    if (auftragsart == 1) //Transport
    {
        done = false;
        emit nextState2();
    }
    else if (auftragsart == 2) //Parken
    {
        done = false;
        emit nextState3();
    }
    else if (auftragsart == 3) //Laden
    {
        done = false;
        emit nextState();
    }
    else
    {
        emit nextState4();
    }


    //QVector<int> vektor(9);

}
void SimulatedRobot::S1W(){reset();timer->start(3000);} // Wait

void SimulatedRobot::S2(){SendStatus(100,0);timer->start(3000);} // Zu Pos 1 fahren
void SimulatedRobot::S3(){SendStatus(200+pos1,0);timer->start(1000);} // Greifer schließen
void SimulatedRobot::S4(){SendStatus(200+pos1,1);timer->start(2000);} // Pos 1 verlassen
void SimulatedRobot::S5(){SendStatus(100,1);timer->start(3000);} // Zu Pos 2 Fahren
void SimulatedRobot::S6(){SendStatus(200+pos2,1);timer->start(1000);} // Greifer öffnen
void SimulatedRobot::S7(){SendStatus(200+pos2,0);reset();timer->start(2000);} // Pos 2 verlassen
void SimulatedRobot::S8(){SendStatus(100,0);auftragsart = 0; timer->start(3000);} // Zum Parken fahren

void SimulatedRobot::S9()
{
    if (!done)
    {
        done = true;
        SendStatus(200+pos1,0);
    }
    if (auftragsart == 1) //Transport
    {
        done = false;
        emit nextState();
    }
    else if (auftragsart == 3) //Laden
    {
        done = false;
        emit nextState2();
    }
    else
    {
        emit nextState4();
    }
}
void SimulatedRobot::S9W(){timer->start(3000);} // Wait

void SimulatedRobot::S10(){SendStatus(100,0);auftragsart = 0;timer->start(3000);} // Zum Laden fahren
void SimulatedRobot::S11(){SendStatus(200+pos1,0);reset();timer->start(5000);} // Akku voll geladen
