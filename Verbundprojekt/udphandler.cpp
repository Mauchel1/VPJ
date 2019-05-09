#include "udphandler.h"
#include <QtMath>

UdpHandler::UdpHandler(quint16 port, QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(port, QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingNavigationData()));
    lastSendValues =  QVector<double>(5);
}


UdpHandler::UdpHandler(bool simulated, QHostAddress ip, quint16 sport, quint16 rport, QObject *parent) : QObject(parent)
{
    this->ip = ip;
    this->receivingport = rport;
    this->sendingport = sport;
    this->simulated = simulated;
    lastSendValues =  QVector<double>(5);

    if (!simulated)
    {
        socket = new QUdpSocket(this);

        //socket->bind(this->ip, rport);
        socket->bind(rport, QUdpSocket::ShareAddress);

        connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingRobotData()));
    }
    else
    {
        r.Start();
        QObject::connect(&r, &SimulatedRobot::StatusDataSimulatedReceived, this, &UdpHandler::simulatedRobotDataReceived);
    }
}

void UdpHandler::simulatedRobotDataReceived(QVector<int> values)
{
    emit StatusDataReceived(values);
}

void UdpHandler::sendRobotAlive(int data)
{
    QVector<double> tempdata(5);
    tempdata[0] = lastSendValues[0];
    tempdata[1] = lastSendValues[1];
    tempdata[2] = lastSendValues[2];
    tempdata[3] = data;
    tempdata[4] = 0;
    WriteData(tempdata);
}

void UdpHandler::WriteData(QVector<double> values)
{
    lastSendValues = values;
    if (simulated)
    {
        r.auftragsart = static_cast<int>(values[0]);
        r.pos1 = static_cast<int>(values[1]);
        r.pos2 = static_cast<int>(values[2]);
    }
    else
    {

        QByteArray Data;
        for(int i = 0; i < 5; i++)
        {
            //Data.append()
            //Data.append(QByteArray::number(values[i]));
            //Data.append(*reinterpret_cast <const char*>(values[i]));
            Data.append(QByteArray::fromRawData(reinterpret_cast<char*>(&values[i]), sizeof(values[i])));
            //Data.append(QByteArray::fromRawData(reinterpret_cast<char*>(&values[i]), sizeof(values[i]) * sizeof (double)));
        }

        //socket->writeDatagram(Data, ip, sendingport);
        //Data.append("Hello from Fertigungsrechner");

        socket->writeDatagram(Data, ip, sendingport);
        //socket->writeDatagram(Data, 192.168.0.14, sendingport);
    }
}

void UdpHandler::readPendingNavigationData()
{
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        processTheNavigationData(datagram);
    }
}

void UdpHandler::readPendingRobotData()
{
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        processTheRobotData(datagram);
    }
}

void UdpHandler::processTheNavigationData(QNetworkDatagram datagram)
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
            vektor[i] = *reinterpret_cast<const double*>(temp.data());
//            qDebug() << i+1 << ": " << *reinterpret_cast<const double*>(temp.data());
//            QByteArray temp2 = QByteArray::fromRawData(temp, 8);
//            qDebug() << "double t2: " << *reinterpret_cast<const double*>(temp2.data());
        }

        prepareNavigationDataforRobot(vektor);
    }
}

void UdpHandler::prepareNavigationDataforRobot(QVector<double> values)
{
    QVector<int> posr1(3);
    QVector<int> posr2(3);
    QVector<int> posr3(3);
    QVector<int> posr4(3);
    QVector<int> posr5(3);

    posr1[0] = static_cast<int>(values[0]);
    posr1[1] = static_cast<int>(values[1]);
    posr1[2] = static_cast<int>(qRadiansToDegrees(values[2]));

    posr2[0] = static_cast<int>(values[3]);
    posr2[1] = static_cast<int>(values[4]);
    posr2[2] = static_cast<int>(qRadiansToDegrees(values[5]));

    posr3[0] = static_cast<int>(values[6]);
    posr3[1] = static_cast<int>(values[7]);
    posr3[2] = static_cast<int>(qRadiansToDegrees(values[8]));

    posr4[0] = static_cast<int>(values[9]);
    posr4[1] = static_cast<int>(values[10]);
    posr4[2] = static_cast<int>(qRadiansToDegrees(values[11]));

    posr5[0] = static_cast<int>(values[12]);
    posr5[1] = static_cast<int>(values[13]);
    posr5[2] = static_cast<int>(qRadiansToDegrees(values[14]));

    emit NavigationDataReceivedR1(posr1);
    emit NavigationDataReceivedR2(posr2);
    emit NavigationDataReceivedR3(posr3);
    emit NavigationDataReceivedR4(posr4);
    emit NavigationDataReceivedR5(posr5);
}

void UdpHandler::processTheRobotData(QNetworkDatagram datagram)
{
    if (datagram.data().length() != 72)
    {
        qDebug() << "Received Navigation Data have wrong dimensions: " << datagram.data().length();
    }
    else
    {
        QVector<int> vektor(9);
        for(int i = 0; i < 9; i ++)
        {
            QByteArray temp = datagram.data().mid(i*8,8);
            vektor[i] = static_cast<int>(*reinterpret_cast<const double*>(temp.data()));
        }

        //prepareRobotData(vektor);
        emit StatusDataReceived(vektor);
    }
}

//void myUDP::prepareRobotData(QVector<double> values)
//{

//    posr1[0] = values[0];
//    posr1[1] = values[1];
//    posr1[2] = values[2];
//    posr2[0] = values[3];
//    posr2[1] = values[4];
//    posr2[2] = values[5];
//    posr3[0] = values[6];
//    posr3[1] = values[7];
//    posr3[2] = values[8];



    //emit StatusDataReceived();
//}


//*********VERALTET**********//

//        while (socket->hasPendingDatagrams()) {
//            qDebug() << socket->pendingDatagramSize();
//            QByteArray datagram;
//            datagram.resize(socket->pendingDatagramSize());
//            QHostAddress sender;
//            quint16 senderPort;

//            socket->readDatagram(datagram.data(), datagram.size(),
//                                    &sender, &senderPort);

//            processTheDatagram(datagram);
//        }


//QByteArray Buffer;
//Buffer.resize((int)socket->pendingDatagramSize());
//QHostAddress sender;
//quint16 senderPort;

//socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

//qDebug() << "UDP Message from: " << sender.toString();
//qDebug() << "UDP port from: " << senderPort;
//qDebug() << "UDP Message: " << Buffer;


