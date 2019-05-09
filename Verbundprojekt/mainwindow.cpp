#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ButtonDefektPlatz = ui->ButtonDefektPlatz;
    ButtonDefektRobot = ui->ButtonDefektRobot;
    ButtonFreeParkplatz = ui->ButtonFreeParkplatz;
    ButtonFreePlatz = ui->ButtonFreePlatz;
    ButtonFreeStation = ui->ButtonFreeStation;
    ButtonNotDefektPlatz = ui->ButtonNotDefektPlatz;
    ButtonNotDefektRobot = ui->ButtonNotDefektRobot;
    ButtonBlockAuftrag = ui->ButtonAuftragBlocked;

    HardCodeButtons.append(ui->ButtonDefektPlatz);
    HardCodeButtons.append(ui->ButtonDefektRobot);
    HardCodeButtons.append(ui->ButtonFreeParkplatz);
    HardCodeButtons.append(ui->ButtonFreePlatz);
    HardCodeButtons.append(ui->ButtonFreeStation);
    HardCodeButtons.append(ui->ButtonNotDefektPlatz);
    HardCodeButtons.append(ui->ButtonNotDefektRobot);
    HardCodeButtons.append(ui->ButtonAuftragBlocked);

    foreach(QPushButton *b , HardCodeButtons)
    {
        b->setCheckable(true);
    }

    QPixmap pix(":/Images/gray.png");

    S1P0 = ui->S1P0;
    S1P1 = ui->S1P1;
    S1P2 = ui->S1P2;
    S2P0 = ui->S2P0;
    S2P1 = ui->S2P1;
    S2P2 = ui->S2P2;
    S3P0 = ui->S3P0;
    S3P1 = ui->S3P1;
    S3P2 = ui->S3P2;
    S4P0 = ui->S4P0;
    S4P1 = ui->S4P1;
    S4P2 = ui->S4P2;
    S5P0 = ui->S5P0;
    S5P1 = ui->S5P1;
    S5P2 = ui->S5P2;
    S6P0 = ui->S6P0;
    S6P1 = ui->S6P1;
    S6P2 = ui->S6P2;
    S7P0 = ui->S7P0;
    S7P1 = ui->S7P1;
    S7P2 = ui->S7P2;
    S8P0 = ui->S8P0;
    S8P1 = ui->S8P1;
    S8P2 = ui->S8P2;

    S1 = ui->S1;
    S2 = ui->S2;
    S3 = ui->S3;
    S4 = ui->S4;
    S5 = ui->S5;
    S6 = ui->S6;
    S7 = ui->S7;
    S8 = ui->S8;

    L1 = ui->L1;
    L2 = ui->L2;
    P1 = ui->P1;
    P2 = ui->P2;
    P3 = ui->P3;
    P4 = ui->P4;

    R1 = ui->R1;
    R2 = ui->R2;
    R3 = ui->R3;
    R4 = ui->R4;

    S1->SetId(10);
    S2->SetId(20);
    S3->SetId(30);
    S4->SetId(40);
    S5->SetId(50);
    S6->SetId(60);
    S7->SetId(70);
    S8->SetId(80);
    P1->SetId(1);
    P2->SetId(2);
    P3->SetId(3);
    P4->SetId(4);
    L1->SetId(5);
    L2->SetId(6);

    R1->SetId(1);
    R2->SetId(2);
    R3->SetId(3);
    R4->SetId(4);

    S1P0->SetId(10);
    S1P1->SetId(11);
    S1P2->SetId(12);
    S2P0->SetId(20);
    S2P1->SetId(21);
    S2P2->SetId(22);
    S3P0->SetId(30);
    S3P1->SetId(31);
    S3P2->SetId(32);
    S4P0->SetId(40);
    S4P1->SetId(41);
    S4P2->SetId(42);
    S5P0->SetId(50);
    S5P1->SetId(51);
    S5P2->SetId(52);
    S6P0->SetId(60);
    S6P1->SetId(61);
    S6P2->SetId(62);
    S7P0->SetId(70);
    S7P1->SetId(71);
    S7P2->SetId(72);
    S8P0->SetId(80);
    S8P1->SetId(81);
    S8P2->SetId(82);

    ui->S1P0->setPixmap(pix.scaled(ui->S1P0->width(), ui->S1P0->height(), Qt::KeepAspectRatio));
    ui->S1P1->setPixmap(pix.scaled(ui->S1P1->width(), ui->S1P1->height(), Qt::KeepAspectRatio));
    ui->S1P2->setPixmap(pix.scaled(ui->S1P2->width(), ui->S1P2->height(), Qt::KeepAspectRatio));
    ui->S2P0->setPixmap(pix.scaled(ui->S2P0->width(), ui->S2P0->height(), Qt::KeepAspectRatio));
    ui->S2P1->setPixmap(pix.scaled(ui->S2P1->width(), ui->S2P1->height(), Qt::KeepAspectRatio));
    ui->S2P2->setPixmap(pix.scaled(ui->S2P2->width(), ui->S2P2->height(), Qt::KeepAspectRatio));
    ui->S3P0->setPixmap(pix.scaled(ui->S3P0->width(), ui->S3P0->height(), Qt::KeepAspectRatio));
    ui->S3P1->setPixmap(pix.scaled(ui->S3P1->width(), ui->S3P1->height(), Qt::KeepAspectRatio));
    ui->S3P2->setPixmap(pix.scaled(ui->S3P2->width(), ui->S3P2->height(), Qt::KeepAspectRatio));
    ui->S4P0->setPixmap(pix.scaled(ui->S4P0->width(), ui->S4P0->height(), Qt::KeepAspectRatio));
    ui->S4P1->setPixmap(pix.scaled(ui->S4P1->width(), ui->S4P1->height(), Qt::KeepAspectRatio));
    ui->S4P2->setPixmap(pix.scaled(ui->S4P2->width(), ui->S4P2->height(), Qt::KeepAspectRatio));
    ui->S5P0->setPixmap(pix.scaled(ui->S5P0->width(), ui->S5P0->height(), Qt::KeepAspectRatio));
    ui->S5P1->setPixmap(pix.scaled(ui->S5P1->width(), ui->S5P1->height(), Qt::KeepAspectRatio));
    ui->S5P2->setPixmap(pix.scaled(ui->S5P2->width(), ui->S5P2->height(), Qt::KeepAspectRatio));
    ui->S6P0->setPixmap(pix.scaled(ui->S6P0->width(), ui->S6P0->height(), Qt::KeepAspectRatio));
    ui->S6P1->setPixmap(pix.scaled(ui->S6P1->width(), ui->S6P1->height(), Qt::KeepAspectRatio));
    ui->S6P2->setPixmap(pix.scaled(ui->S6P2->width(), ui->S6P2->height(), Qt::KeepAspectRatio));
    ui->S7P0->setPixmap(pix.scaled(ui->S7P0->width(), ui->S7P0->height(), Qt::KeepAspectRatio));
    ui->S7P1->setPixmap(pix.scaled(ui->S7P1->width(), ui->S7P1->height(), Qt::KeepAspectRatio));
    ui->S7P2->setPixmap(pix.scaled(ui->S7P2->width(), ui->S7P2->height(), Qt::KeepAspectRatio));
    ui->S8P0->setPixmap(pix.scaled(ui->S8P0->width(), ui->S8P0->height(), Qt::KeepAspectRatio));
    ui->S8P1->setPixmap(pix.scaled(ui->S8P1->width(), ui->S8P1->height(), Qt::KeepAspectRatio));
    ui->S8P2->setPixmap(pix.scaled(ui->S8P2->width(), ui->S8P2->height(), Qt::KeepAspectRatio));

    QPixmap pixP(":/Images/ParkplatzFrei.png");

    P1->setPixmap(pixP.scaled(P1->width(), P1->height(), Qt::KeepAspectRatio));
    P2->setPixmap(pixP.scaled(P2->width(), P2->height(), Qt::KeepAspectRatio));
    P3->setPixmap(pixP.scaled(P3->width(), P3->height(), Qt::KeepAspectRatio));
    P4->setPixmap(pixP.scaled(P4->width(), P4->height(), Qt::KeepAspectRatio));

    QPixmap pixL(":/Images/LadestationFrei.png");

    L1->setPixmap(pixL.scaled(L1->width(), L1->height(), Qt::KeepAspectRatio));
    L2->setPixmap(pixL.scaled(L2->width(), L2->height(), Qt::KeepAspectRatio));

    QPixmap pixS(":/Images/StationReserviert.png");

    S1->setPixmap(pixS.scaled(S1->width(), S1->height(), Qt::KeepAspectRatio));
    S2->setPixmap(pixS.scaled(S2->width(), S2->height(), Qt::KeepAspectRatio));
    S3->setPixmap(pixS.scaled(S3->width(), S3->height(), Qt::KeepAspectRatio));
    S4->setPixmap(pixS.scaled(S4->width(), S4->height(), Qt::KeepAspectRatio));
    S5->setPixmap(pixS.scaled(S5->width(), S5->height(), Qt::KeepAspectRatio));
    S6->setPixmap(pixS.scaled(S6->width(), S6->height(), Qt::KeepAspectRatio));
    S7->setPixmap(pixS.scaled(S7->width(), S7->height(), Qt::KeepAspectRatio));
    S8->setPixmap(pixS.scaled(S8->width(), S8->height(), Qt::KeepAspectRatio));
    S1->setHidden(true);
    S2->setHidden(true);
    S3->setHidden(true);
    S4->setHidden(true);
    S5->setHidden(true);
    S6->setHidden(true);
    S7->setHidden(true);
    S8->setHidden(true);



    //S1P1 = ui->S1P1;
    //StationClickable->append(l);
    //Label1 = ui->S8P2;

    Robotino1 = ui->Robotino1;
    Robotino2 = ui->Robotino2;
    Robotino3 = ui->Robotino3;
    Robotino4 = ui->Robotino4;
    Robotino5 = ui->Robotino5;

    AuftragListWidget = ui->AuftragsListWidget;

    AkkuR1 = ui->AkkuR1;
    AkkuR2 = ui->AkkuR2;
    AkkuR3 = ui->AkkuR3;
    AkkuR4 = ui->AkkuR4;
    AkkuR5 = ui->AkkuR5;

    AkkukleinR1 = ui->AkkukleinR1;
    AkkukleinR2 = ui->AkkukleinR2;
    AkkukleinR3 = ui->AkkukleinR3;
    AkkukleinR4 = ui->AkkukleinR4;
    AkkukleinR5 = ui->AkkukleinR5;

    AkkukleinR1->setOrientation(Qt::Vertical);
    AkkukleinR2->setOrientation(Qt::Vertical);
    AkkukleinR3->setOrientation(Qt::Vertical);
    AkkukleinR4->setOrientation(Qt::Vertical);

    AkkukleinR5->setHidden(true);

    AliveR1 = ui->Robot1Alive;
    AliveR2 = ui->Robot2Alive;
    AliveR3 = ui->Robot3Alive;
    AliveR4 = ui->Robot4Alive;
    AliveR5 = ui->Robot5Alive;

//    QProgressBar {
//        border: 2px solid grey;
//        border-radius: 5px;
//        text-align: right;
//     }
//    QProgressBar::chunk {
//        background-color: #05B8CC;
//        width: 2px;
//    }

    DebugTextArea = ui->debugTextEdit;

    blinktimer = new QTimer();
    blinktimer->setSingleShot(false);
    blinktimer->setInterval(500);
    QObject::connect(blinktimer, &QTimer::timeout, this, &MainWindow::ToggleAliveRobotino);
    //QObject::connect(blinktimer, &QTimer::timeout, this, &MainWindow::on_pushButton_clicked); //TODO für echtes Programm entfernen
    blinktimer->start();
}

void MainWindow::WriteToDebugTextArea(QString message)
{
    QString temp = QTime::currentTime().toString() + ": " + message;
    DebugTextArea->append(temp);
}

void MainWindow::UpdateRobotino1Position(QVector<int> newPosition){    UpdateRobotinoPosition(newPosition, Robotino1, ui->R1, G1, D1, H1, false);}
void MainWindow::UpdateRobotino2Position(QVector<int> newPosition){    UpdateRobotinoPosition(newPosition, Robotino2, ui->R2, G2, D2, H2, false);}
void MainWindow::UpdateRobotino3Position(QVector<int> newPosition){    UpdateRobotinoPosition(newPosition, Robotino3, ui->R3, G3, D3, H3, false);}
void MainWindow::UpdateRobotino4Position(QVector<int> newPosition){    UpdateRobotinoPosition(newPosition, Robotino4, ui->R4, G4, D4, H4, false);}
void MainWindow::UpdateRobotino5Position(QVector<int> newPosition){    UpdateRobotinoPosition(newPosition, Robotino5, ui->R5, G5, D5, H5, true);}

void MainWindow::UpdateRobotinoPixmap(int RobotID)
{
    switch (RobotID) {
    case 1:
        UpdateRobotinoXPixmap(ui->R1, G1, D1, H1, false);
        break;
    case 2:
        UpdateRobotinoXPixmap(ui->R2, G2, D2, H2, false);
        break;
    case 3:
        UpdateRobotinoXPixmap(ui->R3, G3, D3, H3, false);
        break;
    case 4:
        UpdateRobotinoXPixmap(ui->R4, G4, D4, H4, false);
        break;
    default:
        break;
    }
}

void MainWindow::UpdateRobotino1Akku(int percent){    UpdateRobotinoAkku(percent, AkkuR1, AkkukleinR1);}
void MainWindow::UpdateRobotino2Akku(int percent){    UpdateRobotinoAkku(percent, AkkuR2, AkkukleinR2);}
void MainWindow::UpdateRobotino3Akku(int percent){    UpdateRobotinoAkku(percent, AkkuR3, AkkukleinR3);}
void MainWindow::UpdateRobotino4Akku(int percent){    UpdateRobotinoAkku(percent, AkkuR4, AkkukleinR4);}
void MainWindow::UpdateRobotino5Akku(int percent){    UpdateRobotinoAkku(percent, AkkuR5, AkkukleinR5);}

void MainWindow::UpdateRobotino1Alive(bool alive){    A1 = alive; UpdateRobotinoAlive(1, A1, AliveR1);}
void MainWindow::UpdateRobotino2Alive(bool alive){    A2 = alive; UpdateRobotinoAlive(2, A2, AliveR2);}
void MainWindow::UpdateRobotino3Alive(bool alive){    A3 = alive; UpdateRobotinoAlive(3, A3, AliveR3);}
void MainWindow::UpdateRobotino4Alive(bool alive){    A4 = alive; UpdateRobotinoAlive(4, A4, AliveR4);}
void MainWindow::UpdateRobotino5Alive(bool alive){    A5 = alive; UpdateRobotinoAlive(5, A5, AliveR5);}

void MainWindow::UpdateRobotino1Greifer(bool status){    G1 = status;}
void MainWindow::UpdateRobotino2Greifer(bool status){    G2 = status;}
void MainWindow::UpdateRobotino3Greifer(bool status){    G3 = status;}
void MainWindow::UpdateRobotino4Greifer(bool status){    G4 = status;}
void MainWindow::UpdateRobotino5Greifer(bool status){    G5 = status;}

void MainWindow::UpdateRobotino1Hindernis(int hindernis){    H1 = hindernis;}
void MainWindow::UpdateRobotino2Hindernis(int hindernis){    H2 = hindernis;}
void MainWindow::UpdateRobotino3Hindernis(int hindernis){    H3 = hindernis;}
void MainWindow::UpdateRobotino4Hindernis(int hindernis){    H4 = hindernis;}
void MainWindow::UpdateRobotino5Hindernis(int hindernis){    H5 = hindernis;}

void MainWindow::UpdateRobotinoXPixmap(QLabel *Rlabel, bool G, bool D, int H, bool einhorn)
{
    QPixmap pixmap;
    if (H < 1) //kein Hindernis
    {
        pixmap = G ? QPixmap(":/Images/RobotinoGzu.png") : QPixmap(":/Images/RobotinoGoffen.png");
    }
    else if (H == 1) // unbekanntes Hindernis
    {
        pixmap = QPixmap(":/Images/RobotinoRandRot.png");
//        pixmap = G ? QPixmap(":/Images/RobotinoGzuRandRot.png") : QPixmap(":/Images/RobotinoGoffenRandRot.png");
    }
    else if (H == 2) // Roboter Hindernis
    {
        pixmap = QPixmap(":/Images/RobotinoRandOrange.png");
//        pixmap = G ? QPixmap(":/Images/RobotinoGzuRandOrange.png") : QPixmap(":/Images/RobotinoGoffenRandOrange.png");
    }
    else if (H == 3) // Hindernis kurz erkannt - Auswertung folgt (evtl)
    {
        pixmap = QPixmap(":/Images/RobotinoRandGelb.png");
//        pixmap = G ? QPixmap(":/Images/RobotinoGzuRandGelb.png") : QPixmap(":/Images/RobotinoGoffenRandGelb.png");
    }
    pixmap = D ? QPixmap(":/Images/RobotinoDefect.png") : pixmap;
    pixmap = einhorn ? QPixmap(":/Images/EinHorn.png") : pixmap;
    //QPixmap pixmap(*Rlabel->pixmap());
    Rlabel->setPixmap(pixmap);
}

void MainWindow::UpdateRobotinoPosition(QVector<int> newPosition, QFrame *Robotino, QLabel *Rlabel, bool G, bool D, int H, bool einhorn)
{
    UpdateRobotinoXPixmap(Rlabel, G, D, H, einhorn);

    QMatrix rm;
    rm.rotate(-newPosition[2]);
    QPixmap pixmap = Rlabel->pixmap()->copy().transformed(rm);
    Rlabel->setPixmap(pixmap);

    Robotino->move(newPosition[0]/10, 400-(newPosition[1]/10));
}

void MainWindow::UpdateRobotinoAkku(int percent, QProgressBar *P, QProgressBar *Pklein)
{
    if (percent < 30)
    {
        P->setStyleSheet("QProgressBar::chunk {background-color: red}");
        Pklein->setStyleSheet("QProgressBar::chunk {background-color: red}");
    }
    else if (percent > 77)
    {
        P->setStyleSheet("QProgressBar::chunk {background-color: green}");
        Pklein->setStyleSheet("QProgressBar::chunk {background-color: green}");
    }
    else
    {
        P->setStyleSheet("QProgressBar::chunk {background-color: yellow}");
        Pklein->setStyleSheet("QProgressBar::chunk {background-color: yellow}");
    }
    P->setValue(percent);
    Pklein->setValue(percent);

}

void MainWindow::UpdateRobotinoAlive(int id, bool alive, QPushButton *AliveButton)
{
    if (alive)
    {
        AliveButton->setStyleSheet("QPushButton {background-color: green; border-radius: 6px;}");
    }
    else
    {
        WriteToDebugTextArea("Achtung: Robot " + QString::number(id) + " died!");
        AliveButton->setStyleSheet("QPushButton {background-color: gray; border-radius: 6px;}");
    }
}

void MainWindow::ToggleAliveRobotino()
{
    toggler = !toggler;
    if (A1)
    {
        toggler ? AliveR1->setStyleSheet("QPushButton {background-color: rgb(0,250,50); border-radius: 6px;}") : AliveR1->setStyleSheet("QPushButton {background-color: green; border-radius: 6px;}");
    }
    if (A2)
    {
        toggler ? AliveR2->setStyleSheet("QPushButton {background-color: rgb(0,250,50); border-radius: 6px;}") : AliveR2->setStyleSheet("QPushButton {background-color: green; border-radius: 6px;}");
    }
    if (A3)
    {
        toggler ? AliveR3->setStyleSheet("QPushButton {background-color: rgb(0,250,50); border-radius: 6px;}") : AliveR3->setStyleSheet("QPushButton {background-color: green; border-radius: 6px;}");
    }
    if (A4)
    {
        toggler ? AliveR4->setStyleSheet("QPushButton {background-color: rgb(0,250,50); border-radius: 6px;}") : AliveR4->setStyleSheet("QPushButton {background-color: green; border-radius: 6px;}");
    }
    if (A5)
    {
        toggler ? AliveR5->setStyleSheet("QPushButton {background-color: rgb(0,250,50); border-radius: 6px;}") : AliveR5->setStyleSheet("QPushButton {background-color: green; border-radius: 6px;}");
    }
}

void MainWindow::UpdateStation(int ID, bool newState)
{

    if (ID < 20)
    {
        S1->setHidden(newState);
    }
    else if (ID < 30)
    {
        S2->setHidden(newState);
    }
    else if (ID < 40)
    {
        S3->setHidden(newState);
    }
    else if (ID < 50)
    {
        S4->setHidden(newState);
    }
    else if (ID < 60)
    {
        S5->setHidden(newState);
    }
    else if (ID < 70)
    {
        S6->setHidden(newState);
    }
    else if (ID < 80)
    {
        S7->setHidden(newState);
    }
    else
    {
        S8->setHidden(newState);
    }
}

void MainWindow::UpdateStationToolTip(int ID, QString temp)
{
    switch (ID)
    {
    case 11:
        ui->S1P1->setToolTip(temp);
        break;
    case 12:
        ui->S1P2->setToolTip(temp);
        break;
    case 21:
        ui->S2P1->setToolTip(temp);
        break;
    case 22:
        ui->S2P2->setToolTip(temp);
        break;
    case 31:
        ui->S3P1->setToolTip(temp);
        break;
    case 32:
        ui->S3P2->setToolTip(temp);
        break;
    case 41:
        ui->S4P1->setToolTip(temp);
        break;
    case 42:
        ui->S4P2->setToolTip(temp);
        break;
    case 51:
        ui->S5P1->setToolTip(temp);
        break;
    case 52:
        ui->S5P2->setToolTip(temp);
        break;
    case 61:
        ui->S6P1->setToolTip(temp);
        break;
    case 62:
        ui->S6P2->setToolTip(temp);
        break;
    case 71:
        ui->S7P1->setToolTip(temp);
        break;
    case 72:
        ui->S7P2->setToolTip(temp);
        break;
    case 81:
        ui->S8P1->setToolTip(temp);
        break;
    case 82:
        ui->S8P2->setToolTip(temp);
        break;
    default:
        break;
    }
}

void MainWindow::UpdateParkplatz(int ID, int newState)
{
    QPixmap pix;

    switch (newState)
    {
    case 1:
        pix = (ID > 4) ? QPixmap(":/Images/LadestationReserviert.png"): QPixmap(":/Images/ParkplatzReserviert.png");
        break;
    case 0:
        pix = (ID > 4) ? QPixmap(":/Images/LadestationFrei.png"): QPixmap(":/Images/ParkplatzFrei.png");
        break;
    default:
        pix = QPixmap(":/Images/ParkplatzFrei.png");
    }

    switch (ID)
    {
    case 1:
        P1->setPixmap(pix.scaled(P1->width(), P1->height(), Qt::KeepAspectRatio));
        break;
    case 2:
        P2->setPixmap(pix.scaled(P2->width(), P2->height(), Qt::KeepAspectRatio));
        break;
    case 3:
        P3->setPixmap(pix.scaled(P3->width(), P3->height(), Qt::KeepAspectRatio));
        break;
    case 4:
        P4->setPixmap(pix.scaled(P4->width(), P4->height(), Qt::KeepAspectRatio));
        break;
    case 5:
        L1->setPixmap(pix.scaled(L1->width(), L1->height(), Qt::KeepAspectRatio));
        break;
    case 6:
        L2->setPixmap(pix.scaled(L2->width(), L2->height(), Qt::KeepAspectRatio));
        break;
    default:
        break;
    }
}


void MainWindow::UpdateStationsplatz(int ID, int newState)
{
    QPixmap pix;

    switch (newState)
    {
    case 0:
        pix = QPixmap(":/Images/gray.png");
        break;
    case 1:
        pix = QPixmap(":/Images/gelb.png");
        break;
    case 2:
        pix = QPixmap(":/Images/orange.png");
        break;
    case 3:
        pix = QPixmap(":/Images/green.png");
        break;
    case 4:
        pix = QPixmap(":/Images/red.png");
        break;
    default:
        pix = QPixmap(":/Images/gray.png");
    }

    switch (ID)
    {
    case 11:
        ui->S1P1->setPixmap(pix.scaled(ui->S1P1->width(), ui->S1P1->height(), Qt::KeepAspectRatio));
        break;
    case 12:
        ui->S1P2->setPixmap(pix.scaled(ui->S1P2->width(), ui->S1P2->height(), Qt::KeepAspectRatio));
        break;
    case 21:
        ui->S2P1->setPixmap(pix.scaled(ui->S2P1->width(), ui->S2P1->height(), Qt::KeepAspectRatio));
        break;
    case 22:
        ui->S2P2->setPixmap(pix.scaled(ui->S2P2->width(), ui->S2P2->height(), Qt::KeepAspectRatio));
        break;
    case 31:
        ui->S3P1->setPixmap(pix.scaled(ui->S3P1->width(), ui->S3P1->height(), Qt::KeepAspectRatio));
        break;
    case 32:
        ui->S3P2->setPixmap(pix.scaled(ui->S3P2->width(), ui->S3P2->height(), Qt::KeepAspectRatio));
        break;
    case 41:
        ui->S4P1->setPixmap(pix.scaled(ui->S4P1->width(), ui->S4P1->height(), Qt::KeepAspectRatio));
        break;
    case 42:
        ui->S4P2->setPixmap(pix.scaled(ui->S4P2->width(), ui->S4P2->height(), Qt::KeepAspectRatio));
        break;
    case 51:
        ui->S5P1->setPixmap(pix.scaled(ui->S5P1->width(), ui->S5P1->height(), Qt::KeepAspectRatio));
        break;
    case 52:
        ui->S5P2->setPixmap(pix.scaled(ui->S5P2->width(), ui->S5P2->height(), Qt::KeepAspectRatio));
        break;
    case 61:
        ui->S6P1->setPixmap(pix.scaled(ui->S6P1->width(), ui->S6P1->height(), Qt::KeepAspectRatio));
        break;
    case 62:
        ui->S6P2->setPixmap(pix.scaled(ui->S6P2->width(), ui->S6P2->height(), Qt::KeepAspectRatio));
        break;
    case 71:
        ui->S7P1->setPixmap(pix.scaled(ui->S7P1->width(), ui->S7P1->height(), Qt::KeepAspectRatio));
        break;
    case 72:
        ui->S7P2->setPixmap(pix.scaled(ui->S7P2->width(), ui->S7P2->height(), Qt::KeepAspectRatio));
        break;
    case 81:
        ui->S8P1->setPixmap(pix.scaled(ui->S8P1->width(), ui->S8P1->height(), Qt::KeepAspectRatio));
        break;
    case 82:
        ui->S8P2->setPixmap(pix.scaled(ui->S8P2->width(), ui->S8P2->height(), Qt::KeepAspectRatio));
        break;
    default:
        break;
    }
}

void MainWindow::SetTimestamps(QList<Timestamp*> timestamps)
{
    ui->infoArea->clear();
    foreach (Timestamp *timestamp, timestamps)
    {
        if (timestamp->Status() == 1)
        {
            ui->infoArea->append(timestamp->TimeString() + ": Werkstueck " + QString::number(timestamp->Werkstueck()) + " an Station " + QString::number(timestamp->Platz()) + " angemeldet");
        }
        else
        {
            ui->infoArea->append(timestamp->TimeString() + ": Werkstueck " + QString::number(timestamp->Werkstueck()) + " an Station " + QString::number(timestamp->Platz()) + " abgemeldet");
        }
    }
}

void MainWindow::UpdateProzessLabelTooltip(Prozess *p)
{
    QString temp;
    foreach (Prozessschritt *item, p->Prozessschritte)
    {
        temp += "S";
        temp += QString::number(item->Station());
        temp += " (";
        temp += QString::number(item->Dauer());
        temp += "sek)\n";
    }
    temp.chop(1);
    switch (p->referenzId)
    {
    case 1:
        ui->prozess1label->setToolTip(temp);
        break;
    case 2:
        ui->prozess2label->setToolTip(temp);
        break;
    case 3:
        ui->prozess3label->setToolTip(temp);
        break;
    case 4:
        ui->prozess4label->setToolTip(temp);
        break;
    case 5:
        ui->prozess5label->setToolTip(temp);
        break;
    default:
        break;
    }

}

void MainWindow::AddAuftragsItem(Auftrag *a)
{

    //https://blog.manash.me/quick-qt-3-how-to-dynamically-create-qlistwidgetitem-and-add-it-onto-qlistwidget-4bca5bacaa01
    //Creating a new list widget item whose parent is the listwidget itself
    QListWidgetItem *listWidgetItem = new QListWidgetItem(AuftragListWidget);
    //Adding the item to the listwidget
    AuftragListWidget->addItem(listWidgetItem);
    //Creating an object of the designed widget which is to be added to the listwidget
    Auftragsitem *auftragsItem = new Auftragsitem(a);
    auftragsItem->SetLabelText("Auftrag " + QString::number(a->id));
    auftragsItem->UpdateAuftragsFortschritt();
    //Making sure that the listWidgetItem has the same size as the TheWidgetItem
    listWidgetItem->setSizeHint (auftragsItem->sizeHint());
    //Finally adding the itemWidget to the list
    AuftragListWidget->setItemWidget(listWidgetItem, auftragsItem);
    listWidgetItem->setWhatsThis(WhatsThis[0]);


    int itemrow = AuftragListWidget->row(listWidgetItem);

    foreach (Prozess *p, a->Prozesse)
    {
        Prozessitem *prozessItem = new Prozessitem(p);
        prozessItem->SetLabelText("Prozess " + QString::number(p->referenzId));
        prozessItem->UpdateProzessFortschritt();


        QListWidgetItem *widgetItem = new QListWidgetItem();

        AuftragListWidget->insertItem(itemrow+1, widgetItem);

        AuftragListWidget->setItemWidget(widgetItem, prozessItem);
        widgetItem->setSizeHint(prozessItem->sizeHint());
        //widgetItem->setSizeHint(QSize(161, 35));
        widgetItem->setHidden(true);
        widgetItem->setWhatsThis(WhatsThis[1]);
        QString temp = "Werkstueck: " + QString::number(p->lfdId);
        prozessItem->setToolTip(temp);
        itemrow++;
    }
}

void MainWindow::on_sendAuftrag_clicked()
{

    QVector<int> returnvalues(5);
    returnvalues[0] = ui->prozess1number->value();
    returnvalues[1] = ui->prozess2number->value();
    returnvalues[2] = ui->prozess3number->value();
    returnvalues[3] = ui->prozess4number->value();
    returnvalues[4] = ui->prozess5number->value();

    ui->prozess1number->setValue(0);
    ui->prozess2number->setValue(0);
    ui->prozess3number->setValue(0);
    ui->prozess4number->setValue(0);
    ui->prozess5number->setValue(0);
    emit NeuerAuftrag(returnvalues);
    //WriteToDebugTextArea(QString::number(ui->prozess1number->value()));
    //<< "HI";//<< ui->prozess1number->value() << ui->prozess2number->value() << ui->prozess3number->value() << ui->prozess4number->value() << ui->prozess5number->value();
}

void MainWindow::on_sendProzess_clicked()
{

    Prozess *p = new Prozess();

    if (ui->prozessstation1enabled->isChecked()){
        Prozessschritt *schritt = new Prozessschritt(ui->prozessstation1number->value(), ui->prozessstation1dauer->value());
        p->Prozessschritte.append(schritt);
    }
    if (ui->prozessstation2enabled->isChecked()){
        Prozessschritt *schritt = new Prozessschritt(ui->prozessstation2number->value(), ui->prozessstation2dauer->value());
        p->Prozessschritte.append(schritt);
    }
    if (ui->prozessstation3enabled->isChecked()){
        Prozessschritt *schritt = new Prozessschritt(ui->prozessstation3number->value(), ui->prozessstation3dauer->value());
        p->Prozessschritte.append(schritt);
    }
    if (ui->prozessstation4enabled->isChecked()){
        Prozessschritt *schritt = new Prozessschritt(ui->prozessstation4number->value(), ui->prozessstation4dauer->value());
        p->Prozessschritte.append(schritt);
    }
    if (ui->prozessstation5enabled->isChecked()){
        Prozessschritt *schritt = new Prozessschritt(ui->prozessstation5number->value(), ui->prozessstation5dauer->value());
        p->Prozessschritte.append(schritt);
    }

    emit NeuerProzess(p);
}

void MainWindow::StationClicked(int id)
{
    //WriteToDebugTextArea("Angeklicked!!! " + QString::number(id));

    QPushButton *p = GetPressedHardCodeButton();
    if (p == nullptr) //defaultmode - no special button pressed
    {
        emit GetTimestampsOnStationClicked(id);
    }
    else if (p == ButtonDefektPlatz)
    {
        emit HardCodeStationsplatzStatus(id, 4);
    }
    else if (p == ButtonFreeStation)
    {
        emit HardCodeStationStatus(id, 0);
    }
    else if (p == ButtonFreePlatz)
    {
        emit HardCodeStationsplatzStatus(id, 0);
    }
    else if (p == ButtonNotDefektPlatz)
    {
        emit HardCodeStationsplatzStatus(id, 0);
    }
}

void MainWindow::ParkplatzClicked(int id)
{
    QPushButton *p = GetPressedHardCodeButton();
    if (p == nullptr) //defaultmode - no special button pressed
    {
    }
    else if (p == ButtonFreeParkplatz)
    {
        emit HardCodeParkplatzStatus(id, 0);
    }
}

void MainWindow::RobotClicked(int id)
{
    QPushButton *p = GetPressedHardCodeButton();
    if (p == nullptr) //defaultmode - no special button pressed
    {

    }
    else if (p == ButtonDefektRobot)
    {
        if (id == 1) {D1 = true;}
        else if (id == 2) {D2 = true;}
        else if (id == 3) {D3 = true;}
        else if (id == 4) {D4 = true;}
        emit HardCodeRobotDefekt(id, true);
    }
    else if (p == ButtonNotDefektRobot)
    {
        if (id == 1) {D1 = false;}
        else if (id == 2) {D2 = false;}
        else if (id == 3) {D3 = false;}
        else if (id == 4) {D4 = false;}
        emit HardCodeRobotDefekt(id, false);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_S1P1dazu_clicked()
{
    WriteToDebugTextArea("Add Werkstück to Station 1 Position 1");
    emit AddS1P1();
}

void MainWindow::on_S1P2dazu_clicked()
{
    WriteToDebugTextArea("Add Werkstück to Station 1 Position 2");
    emit AddS1P2();
}

void MainWindow::on_S8P1weg_clicked()
{
    WriteToDebugTextArea("Remove Werkstück from Station 8 Position 1");
    emit RemoveS8P1();
}

void MainWindow::on_S8P2weg_clicked()
{
    WriteToDebugTextArea("Remove Werkstück from Station 8 Position 2");
    emit RemoveS8P2();
}

void MainWindow::on_AuftragsListWidget_itemClicked(QListWidgetItem *item)
{
    if ((item->whatsThis() == WhatsThis[0]))
    {
        int itemrow = AuftragListWidget->row(item);
        while (true)
        {
            QListWidgetItem* tempitem = AuftragListWidget->item(itemrow+1);
            if (tempitem == nullptr || (tempitem->whatsThis() == WhatsThis[0]))
            {
                break;
            }

            tempitem->setHidden(!tempitem->isHidden());
            //tempitem->setSizeHint(QSize(100, 45));
            itemrow++;
            continue;
        }
    }
    else if (item->whatsThis() == WhatsThis[1])
    {
        Prozessitem *pi = dynamic_cast<Prozessitem*>(AuftragListWidget->itemWidget(item));
        QPushButton *p = GetPressedHardCodeButton();
        if (p == nullptr) //defaultmode - no special button pressed
        {
        }
        else if (p == ButtonBlockAuftrag)
        {
            pi->prozess->SetBlocked();
            pi->UpdateProzessBlocked();
            //TODO
        }
    }
    //TODO DOKU: https://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast
    //Auftragsitem *ai = dynamic_cast<Auftragsitem*>(AuftragFortschritt->itemWidget(item));
}

void MainWindow::on_AuftragsListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (item->whatsThis() == WhatsThis[1])
    {
        Prozessitem *pi = dynamic_cast<Prozessitem*>(AuftragListWidget->itemWidget(item));
        emit GetTimestampsOnProzessClicked(pi->prozess->lfdId);
    }
}

void MainWindow::on_debugButton1_clicked()
{


    //WriteToDebugTextArea(QString::number(liste.at(0)) + " " + QString::number(liste.at(1)) + " " + QString::number(liste.at(2)) + " " + QString::number(liste.at(3)));
//    QVector<double> testdata(5);
//    testdata[0] = 1;
//    testdata[1] = 20;
//    testdata[2] = 70;
//    testdata[3] = 50;
//    testdata[4] = 20;

    //int i = 2;


    //emit DebugPressed();
}

QPushButton* MainWindow::GetPressedHardCodeButton()
{
    foreach(QPushButton *b , HardCodeButtons)
    {
        if (b->isChecked())
        {
            return b;
        }
    }
    return nullptr;
}

void MainWindow::ResetButtonsExeptOne(QPushButton *b)
{
    ui->paintingarea->setStyleSheet("background-color: rgb(230, 120, 120)");
    foreach(QPushButton *b , HardCodeButtons)
    {
        b->setChecked(false);
    }
    b->setChecked(true);
}

void MainWindow::on_ButtonDefektPlatz_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonDefektPlatz);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonDefektRobot_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonDefektRobot);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonNotDefektPlatz_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonNotDefektPlatz);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonNotDefektRobot_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonNotDefektRobot);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonFreeParkplatz_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonFreeParkplatz);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonFreeStation_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonFreeStation);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonFreePlatz_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonFreePlatz);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_ButtonAuftragBlocked_clicked(bool checked)
{
    if (checked)
    {
        ResetButtonsExeptOne(ButtonBlockAuftrag);
    }
    else
    {
        ui->paintingarea->setStyleSheet("background-color: rgb(255, 255, 255)");
    }
}

void MainWindow::on_pushButton_clicked()
{
        QVector<double> testdata(5);
        testdata[0] = 01;
        testdata[1] = 06;
        testdata[2] = 00;
        testdata[3] = 00;
        testdata[4] = 00;
        emit EinhornLaden(testdata);
}

void MainWindow::on_Pause_clicked(bool checked)
{
    emit PauseClicked(checked);
}

void MainWindow::on_pushButton_2_clicked()
{
    QVector<double> testdata(5);
    testdata[0] = 00;
    testdata[1] = 06;
    testdata[2] = 00;
    testdata[3] = 00;
    testdata[4] = 00;
    emit EinhornLaden(testdata);

}
