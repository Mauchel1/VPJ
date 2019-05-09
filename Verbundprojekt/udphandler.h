#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QtNetwork>
#include <QUdpSocket>
#include "simulatedrobot.h"


class UdpHandler : public QObject
{
    Q_OBJECT
public:
    explicit UdpHandler(quint16 port, QObject *parent = nullptr);
    explicit UdpHandler(bool simulated, QHostAddress ip, quint16 sport, quint16 rport, QObject *parent = nullptr);
    void WriteData(QVector<double> values);
private:
    void processTheNavigationData(QNetworkDatagram datagram);
    void prepareNavigationDataforRobot(QVector<double> values);
    void processTheRobotData(QNetworkDatagram datagram);
    void prepareRobotData(QVector<double> values);

signals:
    void NavigationDataReceivedR1(QVector<int> values);
    void NavigationDataReceivedR2(QVector<int> values);
    void NavigationDataReceivedR3(QVector<int> values);
    void NavigationDataReceivedR4(QVector<int> values);
    void NavigationDataReceivedR5(QVector<int> values);

    void StatusDataReceived(QVector<int> values);

public slots:
    void readPendingRobotData();
    void readPendingNavigationData();
    void simulatedRobotDataReceived(QVector<int> values);
    void sendRobotAlive(int data);

private:
    QUdpSocket *socket;
    QHostAddress ip;
    quint16 receivingport;
    quint16 sendingport;

    QVector<double> lastSendValues;
    bool simulated;
    SimulatedRobot r;
};

#endif // UDP_H
