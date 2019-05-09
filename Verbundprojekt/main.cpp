#include "mainwindow.h"
#include <QApplication>
#include "fertigungsplanung.h"
#include "databasehandler.h"
#include "udphandler.h"
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //a.setWindowIcon(QIcon(":/Images/vpj.ico"));
    MainWindow w;
    w.setWindowTitle("VPJ - Monitor");
    //w.setWindowIcon(QIcon(":/Images/vpj.ico"));
    w.show();

    //SIMULATED MODE:
    bool simulated = false;


//    QFile f( "sheet.qss" );
//    if( f.open( QFile::ReadOnly ) )
//    {
//        QString ssheet = QLatin1String( f.readAll() );
//        a.setStyleSheet( ssheet );
//    }


    //qInfo() << "Test1";
    //qDebug() << "Test2";
    //qWarning() << "Test3";
    //qCritical() << "Test4";


    Robotino robot1(1, QHostAddress("192.168.0.11"), 25010, 25011);
    Robotino robot2(2, QHostAddress("192.168.0.12"), 25020, 25012);
    Robotino robot3(3, QHostAddress("192.168.0.13"), 25030, 25013);
    Robotino robot4(4, QHostAddress("192.168.0.14"), 25040, 25014);
    Robotino robot5(5, QHostAddress("192.168.0.25"), 25050, 25015);

    UdpHandler robot1UDP(simulated, robot1.IP(), robot1.PortSend(), robot1.PortReceive());
    UdpHandler robot2UDP(simulated, robot2.IP(), robot2.PortSend(), robot2.PortReceive());
    UdpHandler robot3UDP(simulated, robot3.IP(), robot3.PortSend(), robot3.PortReceive());
    UdpHandler robot4UDP(simulated, robot4.IP(), robot4.PortSend(), robot4.PortReceive());
    UdpHandler robot5UDP(simulated, robot5.IP(), robot5.PortSend(), robot5.PortReceive());

    UdpHandler navUDP(25000);

    // Connect Listener robots
    QObject::connect(&robot1UDP, &UdpHandler::StatusDataReceived, &robot1, &Robotino::UpdateValues);
    QObject::connect(&robot2UDP, &UdpHandler::StatusDataReceived, &robot2, &Robotino::UpdateValues);
    QObject::connect(&robot3UDP, &UdpHandler::StatusDataReceived, &robot3, &Robotino::UpdateValues);
    QObject::connect(&robot4UDP, &UdpHandler::StatusDataReceived, &robot4, &Robotino::UpdateValues);
    QObject::connect(&robot5UDP, &UdpHandler::StatusDataReceived, &robot5, &Robotino::UpdateValues);

    // Connect Listener to NavigationData
    QObject::connect(&navUDP, &UdpHandler::NavigationDataReceivedR1, &robot1, &Robotino::UpdatePosition);
    QObject::connect(&navUDP, &UdpHandler::NavigationDataReceivedR2, &robot2, &Robotino::UpdatePosition);
    QObject::connect(&navUDP, &UdpHandler::NavigationDataReceivedR3, &robot3, &Robotino::UpdatePosition);
    QObject::connect(&navUDP, &UdpHandler::NavigationDataReceivedR4, &robot4, &Robotino::UpdatePosition);
    QObject::connect(&navUDP, &UdpHandler::NavigationDataReceivedR5, &robot5, &Robotino::UpdatePosition);

    //QObject::connect(&robot1UDP, &QObject::destroyed, [] { qDebug() << "Sender got deleted!"; });
    //QObject::connect(&robot1, &QObject::destroyed, [] { qDebug() << "Receiver got deleted!"; });

    QObject::connect(&robot1, &Robotino::PositionChanged, &w, &MainWindow::UpdateRobotino1Position);
    QObject::connect(&robot2, &Robotino::PositionChanged, &w, &MainWindow::UpdateRobotino2Position);
    QObject::connect(&robot3, &Robotino::PositionChanged, &w, &MainWindow::UpdateRobotino3Position);
    QObject::connect(&robot4, &Robotino::PositionChanged, &w, &MainWindow::UpdateRobotino4Position);
    QObject::connect(&robot5, &Robotino::PositionChanged, &w, &MainWindow::UpdateRobotino5Position);

    QObject::connect(&robot1, &Robotino::AkkuChanged, &w, &MainWindow::UpdateRobotino1Akku);
    QObject::connect(&robot2, &Robotino::AkkuChanged, &w, &MainWindow::UpdateRobotino2Akku);
    QObject::connect(&robot3, &Robotino::AkkuChanged, &w, &MainWindow::UpdateRobotino3Akku);
    QObject::connect(&robot4, &Robotino::AkkuChanged, &w, &MainWindow::UpdateRobotino4Akku);

    QObject::connect(&robot1, &Robotino::GetUdpResponse, &robot1UDP, &UdpHandler::sendRobotAlive);
    QObject::connect(&robot2, &Robotino::GetUdpResponse, &robot2UDP, &UdpHandler::sendRobotAlive);
    QObject::connect(&robot3, &Robotino::GetUdpResponse, &robot3UDP, &UdpHandler::sendRobotAlive);
    QObject::connect(&robot4, &Robotino::GetUdpResponse, &robot4UDP, &UdpHandler::sendRobotAlive);

    QObject::connect(&robot1, &Robotino::RobotAliveChanged, &w, &MainWindow::UpdateRobotino1Alive);
    QObject::connect(&robot2, &Robotino::RobotAliveChanged, &w, &MainWindow::UpdateRobotino2Alive);
    QObject::connect(&robot3, &Robotino::RobotAliveChanged, &w, &MainWindow::UpdateRobotino3Alive);
    QObject::connect(&robot4, &Robotino::RobotAliveChanged, &w, &MainWindow::UpdateRobotino4Alive);

    QObject::connect(&robot1, &Robotino::GreiferChanged, &w, &MainWindow::UpdateRobotino1Greifer);
    QObject::connect(&robot2, &Robotino::GreiferChanged, &w, &MainWindow::UpdateRobotino2Greifer);
    QObject::connect(&robot3, &Robotino::GreiferChanged, &w, &MainWindow::UpdateRobotino3Greifer);
    QObject::connect(&robot4, &Robotino::GreiferChanged, &w, &MainWindow::UpdateRobotino4Greifer);

    QObject::connect(&robot1, &Robotino::HindernisChanged, &w, &MainWindow::UpdateRobotino1Hindernis);
    QObject::connect(&robot2, &Robotino::HindernisChanged, &w, &MainWindow::UpdateRobotino2Hindernis);
    QObject::connect(&robot3, &Robotino::HindernisChanged, &w, &MainWindow::UpdateRobotino3Hindernis);
    QObject::connect(&robot4, &Robotino::HindernisChanged, &w, &MainWindow::UpdateRobotino4Hindernis);

    Fertigungsplanung Fertigung;
    w.WriteToDebugTextArea("Fertigungsplanung initialisiert");
    QObject::connect(&w, &MainWindow::NeuerAuftrag, &Fertigung, &Fertigungsplanung::AddAuftrag);
    QObject::connect(&w, &MainWindow::NeuerProzess, &Fertigung, &Fertigungsplanung::AddProzess);

    QObject::connect(&Fertigung, &Fertigungsplanung::DebugAreaString, &w, &MainWindow::WriteToDebugTextArea);

    QObject::connect(&Fertigung.Fs.S1.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S1.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S2.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S2.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S3.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S3.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S4.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S4.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S5.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S5.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S6.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S6.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S7.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S7.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S8.P1, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);
    QObject::connect(&Fertigung.Fs.S8.P2, &Platz::PlatzChanged, &w, &MainWindow::UpdateStationsplatz);

    QObject::connect(&Fertigung.Fs.P1, &Parkplatz::PlatzChanged, &w, &MainWindow::UpdateParkplatz);
    QObject::connect(&Fertigung.Fs.P2, &Parkplatz::PlatzChanged, &w, &MainWindow::UpdateParkplatz);
    QObject::connect(&Fertigung.Fs.P3, &Parkplatz::PlatzChanged, &w, &MainWindow::UpdateParkplatz);
    QObject::connect(&Fertigung.Fs.P4, &Parkplatz::PlatzChanged, &w, &MainWindow::UpdateParkplatz);
    QObject::connect(&Fertigung.Fs.L1, &Parkplatz::PlatzChanged, &w, &MainWindow::UpdateParkplatz);
    QObject::connect(&Fertigung.Fs.L2, &Parkplatz::PlatzChanged, &w, &MainWindow::UpdateParkplatz);

    QObject::connect(&Fertigung, &Fertigungsplanung::StationChanged, &w, &MainWindow::UpdateStation);
    QObject::connect(&Fertigung, &Fertigungsplanung::UpdateRobotinoPixmap, &w, &MainWindow::UpdateRobotinoPixmap);


    //QObject::connect(&Fertigung, &Fertigungsplanung::StationChanged, &w, &MainWindow::UpdateStation);

    QObject::connect(&w, &MainWindow::AddS1P1, &Fertigung.Fs.S1.P1, &Platz::setFullReady);
    QObject::connect(&w, &MainWindow::AddS1P2, &Fertigung.Fs.S1.P2, &Platz::setFullReady);
    QObject::connect(&w, &MainWindow::RemoveS8P1, &Fertigung.Fs.S8.P1, &Platz::setFree);
    QObject::connect(&w, &MainWindow::RemoveS8P2, &Fertigung.Fs.S8.P2, &Platz::setFree);

    QObject::connect(&robot1, &Robotino::GreiferChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino1Greifer);
    QObject::connect(&robot2, &Robotino::GreiferChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino2Greifer);
    QObject::connect(&robot3, &Robotino::GreiferChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino3Greifer);
    QObject::connect(&robot4, &Robotino::GreiferChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino4Greifer);

    QObject::connect(&robot1, &Robotino::UpdateRobotPixmap, &w, &MainWindow::UpdateRobotinoPixmap);
    QObject::connect(&robot2, &Robotino::UpdateRobotPixmap, &w, &MainWindow::UpdateRobotinoPixmap);
    QObject::connect(&robot3, &Robotino::UpdateRobotPixmap, &w, &MainWindow::UpdateRobotinoPixmap);
    QObject::connect(&robot4, &Robotino::UpdateRobotPixmap, &w, &MainWindow::UpdateRobotinoPixmap);

    QObject::connect(&robot1, &Robotino::StatusChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino1Status);
    QObject::connect(&robot2, &Robotino::StatusChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino2Status);
    QObject::connect(&robot3, &Robotino::StatusChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino3Status);
    QObject::connect(&robot4, &Robotino::StatusChanged, &Fertigung, &Fertigungsplanung::UpdateRobotino4Status);

    QObject::connect(&robot1, &Robotino::ErrorOccured, &Fertigung, &Fertigungsplanung::RobotErrorOccured);
    QObject::connect(&robot2, &Robotino::ErrorOccured, &Fertigung, &Fertigungsplanung::RobotErrorOccured);
    QObject::connect(&robot3, &Robotino::ErrorOccured, &Fertigung, &Fertigungsplanung::RobotErrorOccured);
    QObject::connect(&robot4, &Robotino::ErrorOccured, &Fertigung, &Fertigungsplanung::RobotErrorOccured);

    QObject::connect(&Fertigung, &Fertigungsplanung::AuftragAdded, &w, &MainWindow::AddAuftragsItem);
    QObject::connect(&Fertigung, &Fertigungsplanung::ProzessAdded, &w, &MainWindow::UpdateProzessLabelTooltip);
    QObject::connect(&Fertigung, &Fertigungsplanung::UpdateStationToolTip , &w, &MainWindow::UpdateStationToolTip);

    QObject::connect(w.S1P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S1P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S1P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S2P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S2P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S2P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S3P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S3P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S3P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S4P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S4P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S4P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S5P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S5P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S5P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S6P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S6P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S6P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S7P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S7P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S7P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S8P0, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S8P1, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);
    QObject::connect(w.S8P2, &ClickableLabel::clicked, &w, &MainWindow::StationClicked);

    QObject::connect(w.R1, &ClickableLabel::clicked, &w, &MainWindow::RobotClicked);
    QObject::connect(w.R2, &ClickableLabel::clicked, &w, &MainWindow::RobotClicked);
    QObject::connect(w.R3, &ClickableLabel::clicked, &w, &MainWindow::RobotClicked);
    QObject::connect(w.R4, &ClickableLabel::clicked, &w, &MainWindow::RobotClicked);

    QObject::connect(w.P1, &ClickableLabel::clicked, &w, &MainWindow::ParkplatzClicked);
    QObject::connect(w.P2, &ClickableLabel::clicked, &w, &MainWindow::ParkplatzClicked);
    QObject::connect(w.P3, &ClickableLabel::clicked, &w, &MainWindow::ParkplatzClicked);
    QObject::connect(w.P4, &ClickableLabel::clicked, &w, &MainWindow::ParkplatzClicked);
    QObject::connect(w.L1, &ClickableLabel::clicked, &w, &MainWindow::ParkplatzClicked);
    QObject::connect(w.L2, &ClickableLabel::clicked, &w, &MainWindow::ParkplatzClicked);

    QObject::connect(&w, &MainWindow::GetTimestampsOnStationClicked, &Fertigung, &Fertigungsplanung::OnStationClickedNormal);
    QObject::connect(&w, &MainWindow::HardCodeParkplatzStatus, &Fertigung, &Fertigungsplanung::UpdateHardParkplatzStatus);
    QObject::connect(&w, &MainWindow::HardCodeRobotDefekt, &Fertigung, &Fertigungsplanung::UpdateHardRobotDefect);
    QObject::connect(&w, &MainWindow::HardCodeStationStatus, &Fertigung, &Fertigungsplanung::UpdateHardStationStatus);
    QObject::connect(&w, &MainWindow::HardCodeStationsplatzStatus, &Fertigung, &Fertigungsplanung::UpdateHardStationsplatzStatus);

    //   Initialize the database:

    DatabaseHandler dbhandler;
    dbhandler.InitDB();
    w.WriteToDebugTextArea("Datenbank gestartet");

    QObject::connect(&Fertigung.Fs.S1.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S1.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S2.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S2.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S3.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S3.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S4.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S4.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S5.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S5.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S6.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S6.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S7.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S7.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S8.P1, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);
    QObject::connect(&Fertigung.Fs.S8.P2, &Platz::PlatzChanged, &dbhandler, &DatabaseHandler::UpdateStationPlaceStatus);

    QObject::connect(&w, &MainWindow::RemoveS8P1, &dbhandler, &DatabaseHandler::SetS8P1Free);
    QObject::connect(&w, &MainWindow::RemoveS8P2, &dbhandler, &DatabaseHandler::SetS8P2Free);

    QObject::connect(&Fertigung, &Fertigungsplanung::AuftragAdded, &dbhandler, &DatabaseHandler::SendAuftrag);
    QObject::connect(&Fertigung, &Fertigungsplanung::ProzessAdded, &dbhandler, &DatabaseHandler::SendProzess);

    QObject::connect(&robot1, &Robotino::AkkuChanged, &dbhandler, &DatabaseHandler::UpdateRobot1Akku);
    QObject::connect(&robot2, &Robotino::AkkuChanged, &dbhandler, &DatabaseHandler::UpdateRobot2Akku);
    QObject::connect(&robot3, &Robotino::AkkuChanged, &dbhandler, &DatabaseHandler::UpdateRobot3Akku);
    QObject::connect(&robot4, &Robotino::AkkuChanged, &dbhandler, &DatabaseHandler::UpdateRobot4Akku);

    QObject::connect(&robot1, &Robotino::StatusChanged, &dbhandler, &DatabaseHandler::UpdateRobot1Status);
    QObject::connect(&robot2, &Robotino::StatusChanged, &dbhandler, &DatabaseHandler::UpdateRobot2Status);
    QObject::connect(&robot3, &Robotino::StatusChanged, &dbhandler, &DatabaseHandler::UpdateRobot3Status);
    QObject::connect(&robot4, &Robotino::StatusChanged, &dbhandler, &DatabaseHandler::UpdateRobot4Status);


    QObject::connect(&Fertigung, &Fertigungsplanung::StationClicked, &dbhandler, &DatabaseHandler::GetTimeStampsOfArbeitsplatz);
    QObject::connect(&Fertigung, &Fertigungsplanung::WerkstueckClicked, &dbhandler, &DatabaseHandler::GetTimeStampsOfWerkstueck);

    QObject::connect(&w, &MainWindow::GetTimestampsOnProzessClicked, &dbhandler, &DatabaseHandler::GetTimeStampsOfWerkstueck);

    QObject::connect(&dbhandler, &DatabaseHandler::TimestampsOfStationReceived, &w, &MainWindow::SetTimestamps);
    QObject::connect(&dbhandler, &DatabaseHandler::TimestampsOfWerkstueckReceived, &w, &MainWindow::SetTimestamps);


    Fertigung.r1 = &robot1;
    Fertigung.r2 = &robot2;
    Fertigung.r3 = &robot3;
    Fertigung.r4 = &robot4;
    Fertigung.r1UDP = &robot1UDP;
    Fertigung.r2UDP = &robot2UDP;
    Fertigung.r3UDP = &robot3UDP;
    Fertigung.r4UDP = &robot4UDP;
    Fertigung.db = &dbhandler;
    // Inits nach fertigen Connect - Aufrufen
    Fertigung.InitProzesses();

//    QVector<int> testdata(5);
//    testdata[0] = 3000;
//    testdata[1] = 2000;
//    testdata[2] = 90;
//    testdata[3] = 50;
//    testdata[4] = 20;

    //w.UpdateRobotino1Position(testdata);

//    QObject::connect(&w, &MainWindow::DebugPressed, &robot1UDP, &myUDP::WriteData);
//    QObject::connect(&w, &MainWindow::DebugPressed, &robot2UDP, &myUDP::WriteData);
//    QObject::connect(&w, &MainWindow::DebugPressed, &robot3UDP, &myUDP::WriteData);
//    QObject::connect(&w, &MainWindow::DebugPressed, &robot4UDP, &myUDP::WriteData);

    //QObject::connect(&w, &MainWindow::DebugPressed, &dbhandler, &DatabaseHandler::GetLagerWerkstueck);
    //QObject::connect(&w, &MainWindow::DebugPressed, &dbhandler, &DatabaseHandler::IsStationRobotFree);
    //QObject::connect(&w, &MainWindow::DebugPressed, &dbhandler, &DatabaseHandler::GetZielStationsplatzFree);
    QObject::connect(&w, &MainWindow::EinhornLaden, &robot5UDP, &UdpHandler::WriteData);
    QObject::connect(&w, &MainWindow::DebugPressed, &Fertigung, &Fertigungsplanung::DebugSlot);
    QObject::connect(&w, &MainWindow::PauseClicked, &Fertigung, &Fertigungsplanung::UpdatePause);

    Fertigung.AddTransitionsToStates();
    Fertigung.AddStatesToStateMachine();
    QObject::connect(Fertigung.StateWait, &QState::entered, &Fertigung, &Fertigungsplanung::Wait);
    QObject::connect(Fertigung.StateSendLoadingTaskWait, &QState::entered, &Fertigung, &Fertigungsplanung::SendLoadingTaskWait);
    QObject::connect(Fertigung.StateSendPositionTaskWait, &QState::entered, &Fertigung, &Fertigungsplanung::SendPositionTaskWait);
    QObject::connect(Fertigung.StateSendParkingTaskWait, &QState::entered, &Fertigung, &Fertigungsplanung::SendParkingTaskWait);
    QObject::connect(Fertigung.StateCheckParkplatzRobots, &QState::entered, &Fertigung, &Fertigungsplanung::CheckParkplatzRobots);
    QObject::connect(Fertigung.StateCheckRobots, &QState::entered, &Fertigung, &Fertigungsplanung::CheckRobots);
    QObject::connect(Fertigung.StateCheckAkku, &QState::entered, &Fertigung, &Fertigungsplanung::CheckAkku);
    QObject::connect(Fertigung.StateCheckAuftrag, &QState::entered, &Fertigung, &Fertigungsplanung::CheckAuftrag);
    QObject::connect(Fertigung.StateSendTimeout, &QState::entered, &Fertigung, &Fertigungsplanung::SendTimeout);
    QObject::connect(Fertigung.StateSendLoadingTask, &QState::entered, &Fertigung, &Fertigungsplanung::SendLoadingTask);
    QObject::connect(Fertigung.StateSendPositionTask, &QState::entered, &Fertigung, &Fertigungsplanung::SendPositionTask);
    QObject::connect(Fertigung.StateSendParkingTask, &QState::entered, &Fertigung, &Fertigungsplanung::SendParkingTask);

    Fertigung.Start();

    return a.exec();
}

