#include "robotino.h"

Robotino::Robotino(int id, QHostAddress ip, quint16 portreceive, quint16 portsend, QObject *parent) : QObject (parent)
{
    this->id = id;
    this->ip = ip;
    this->portreceive = portreceive;
    this->portsend = portsend;
    this->alivetimer->setSingleShot(true);
    QObject::connect(alivetimer, &QTimer::timeout, this, &Robotino::RobotNotAlive);
    QObject::connect(navigationtimer, &QTimer::timeout, this, &Robotino::UpdatePositionLost);
}

void Robotino::UpdateValues(QVector<int> values)
{

    alivetimer->start(30000); // 30 sekunden timeout für roboter is alive

    if (!isalive)
    {
        isalive = true;
        emit RobotAliveChanged(isalive);
    }

    if (error != values[0])
    {
        error = values[0];

        if (error == 0) // komische Dinge sind auf dem Robotino passiert
        {
            emit ErrorOccured(ID(), 0);
        }
        if (error == 1) // ALLES GUT
        {
            emit ErrorOccured(ID(), 1);
        }
        if (error == 2) // Stein verloren
        {
            emit ErrorOccured(ID(), 2);
        }
        else if (error == 3) // kein Stein greifbar
        {
            emit ErrorOccured(ID(), 3);
        }
        else if (error == 4) // keine Route planbar
        {
            emit ErrorOccured(ID(), 4);
        }
        else if (error == 5) // unbekannter Error
        {
            emit ErrorOccured(ID(), 5);
        }
    }

    if (akku != values[1])
    {
        akku = values[1];
        emit AkkuChanged(values[1]);
    }

    if (hindernis != values[2])
    {
        hindernis = values[2];
        emit HindernisChanged(hindernis);
        emit UpdateRobotPixmap(ID());
    }

   if (udpAlive != values[4])
   {
       udpAlive = values[4];
       emit GetUdpResponse(udpAlive);
   }

    if (status != values[5])
    {
        status = values[5];
        if (status == 0) {emit StatusChanged(0, 0, 0);}
        else if (status >= 100 && status < 200) {emit StatusChanged(1, 0, 0);}
        else if (status >= 200) {
            int p1 = (values[5] /10) % 10;
            int p2 = values[5] % 10;
            position = (p1*10)+p2;
            emit StatusChanged(2, p1, p2);
        }
    }

    bool g = values[6] == 1 ? true: false;

    if (greifer != g)
    {
        greifer = g;
        emit GreiferChanged(g);
    }
}

void Robotino::UpdatePositionLost()
{
    QVector<int> values(3);
    values[0] = 0;
    values[1] = 0;
    values[2] = 0;
    xPos = values[0];
    yPos = values[1];
    angle = values[2];

    emit PositionChanged(values);
}

void Robotino::UpdatePosition(QVector<int> values)
{
    if (abs(xPos - values[0]) > 2 || abs(yPos - values[1]) > 2 || abs(angle - values[2]) > 1)
    {
        if (values[0] == 0 && values[1] == 0 && values [2] == 0)
        {
            // Position des Robotinos verloren
            if (!navigationtimer->isActive())
            {
                navigationtimer->setSingleShot(true);
                navigationtimer->start(5000);
            }
        }
        else
        {
            xPos = values[0];
            yPos = values[1];
            angle = values[2];
            emit PositionChanged(values);
        }
    }
}

void Robotino::RobotNotAlive()
{
    isalive = false;
//    qDebug() << "Robot " + QString::number(id) + " died!";
    emit RobotAliveChanged(isalive);
}

void Robotino::PrintPosition()
{
    qDebug() << "xPos: " << xPos << "   yPos: " << yPos << "    angle: " << angle;
}
