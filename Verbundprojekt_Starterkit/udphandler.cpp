#include "udphandler.h"

UDPHandler::UDPHandler(quint16 port, QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(port, QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingNavigationData()));
}

UDPHandler::UDPHandler(QHostAddress ip, quint16 sport, quint16 rport, QObject *parent) : QObject(parent)
{
    this->ip = ip;
    this->receivingport = rport;
    this->sendingport = sport;

    socket = new QUdpSocket(this);

    //socket->bind(this->ip, rport);
    socket->bind(rport, QUdpSocket::ShareAddress);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingRobotData()));
}

void UDPHandler::readPendingNavigationData()
{
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        //Datagram to progress with
        processTheNavigationData(datagram);
    }
}

void UDPHandler::readPendingRobotData()
{
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        //Datagram to progress with
        processTheRobotData(datagram);
    }
}

void UDPHandler::processTheNavigationData(QNetworkDatagram datagram)
{
    if (datagram.data().length() != 448)
    {
        qDebug() << "Received Navigation Data have wrong dimensions: " << datagram.data().length();
    }
    else
    {
        QVector<double> vektor(56);
        for(int i = 0; i < 56; i ++)
        {
            QByteArray temp = datagram.data().mid(i*8,8);
            vektor[i] = *reinterpret_cast<const int*>(temp.data());
        }
        //Vector to progress with
        vektor;
    }
}

void UDPHandler::processTheRobotData(QNetworkDatagram datagram)
{
    if (datagram.data().length() != 16)
    {
        qDebug() << "Received Navigation Data have wrong dimensions: " << datagram.data().length();
    }
    else
    {
        QVector<int> vektor(2);
        for(int i = 0; i < 2; i ++)
        {
            QByteArray temp = datagram.data().mid(i*8,8);
            vektor[i] = static_cast<int>(*reinterpret_cast<const int*>(temp.data()));
        }

        //prepareRobotData(vektor);
        emit DataReceived(vektor);
    }
}

void UDPHandler::WriteData(QVector<int> values)
{
        QByteArray Data;
        for(int i = 0; i < 5; i++)
        {
            Data.append(QByteArray::fromRawData(reinterpret_cast<char*>(&values[i]), sizeof(values[i])));
        }

        socket->writeDatagram(Data, ip, sendingport);
}
