#ifndef EXAMPLEUDP_H
#define EXAMPLEUDP_H

#include <QObject>
#include <QtNetwork>
#include <QUdpSocket>


class UDPHandler : public QObject
{
    Q_OBJECT
public:
    explicit UDPHandler(quint16 port, QObject *parent = nullptr);
    explicit UDPHandler(QHostAddress ip, quint16 sport, quint16 rport, QObject *parent = nullptr);
    void WriteData(QVector<int> values);

signals:
    void DataReceived(QVector<int> values);

public slots:
    void readPendingRobotData();
    void readPendingNavigationData();

private:
    QUdpSocket *socket;
    QHostAddress ip;
    quint16 receivingport;
    quint16 sendingport;

    void processTheNavigationData(QNetworkDatagram datagram);
    void processTheRobotData(QNetworkDatagram datagram);
};

#endif // EXAMPLEUDP_H
