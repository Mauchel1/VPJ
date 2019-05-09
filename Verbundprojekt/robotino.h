#ifndef ROBOTINO_H
#define ROBOTINO_H

#include <QObject>
#include <QVector>
#include <QtNetwork>


class Robotino : public QObject
{
    Q_OBJECT
public:
    explicit Robotino(int id, QHostAddress ip, quint16 portreceive, quint16 portsend, QObject *parent = nullptr);
    int ID() const {return id;}
    double XPos() const {return xPos;}
    double YPos() const {return yPos;}
    double Angle() const {return angle;}
    int Position() const {return position;}
    int Status() const {return status;}
    int Error() const {return error;}
    int Defect() const {return defect;}
    int Alive() const {return isalive;}
    int Hindernis() const {return hindernis;}
    int Akku() const {return akku;}
    bool Greifer() const {return greifer;}
    QHostAddress IP() const {return ip;}
    quint16 PortSend() const {return portsend;}
    quint16 PortReceive() const {return portreceive;}
    void setXPos(int value) {xPos = value;}
    void setYPos(int value) {yPos = value;}
    void setAngle(int value) {angle = value;}
    void setDefect(bool value) {defect = value;}

private:
    int id;

    int xPos = 0;
    int yPos = 0;
    int angle = 0;

    int position = -1;

    int status = -1;
    int error = 1;
    int hindernis = 0;
    int akku = 80;
    int udpAlive = 0;
    bool greifer = false;
    bool defect = false;

    QHostAddress ip;
    quint16 portreceive;
    quint16 portsend;

    bool isalive = false;
    QTimer *alivetimer = new QTimer();
    QTimer *navigationtimer = new QTimer();

signals:
    void PositionChanged(QVector<int> newPosition);
    void AkkuChanged(int percent);

    void HindernisChanged(int hindernis);

    void StatusChanged(int status, int pos1, int pos2);
    void UpdateRobotPixmap(int RobotID);

    void GreiferChanged(bool status);
    void GetUdpResponse(int data);

    void RobotAliveChanged(bool isAlive);

    void ErrorOccured(int RobotId, int errorID);

public slots:
    void UpdatePosition(QVector<int> values);
    void UpdatePositionLost();
    void UpdateValues(QVector<int> values);
    void PrintPosition();
    void RobotNotAlive();

}

;

#endif // ROBOTINO_H
