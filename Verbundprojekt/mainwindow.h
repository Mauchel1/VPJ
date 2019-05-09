#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QProgressBar>
#include <QTextEdit>
#include <QLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QListWidget>
#include "prozess.h"
#include "auftrag.h"

#include "clickablelabel.h"
#include "auftragsitem.h"
#include "prozessitem.h"
#include "timestamp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void WriteToDebugTextArea(QString message);

    ClickableLabel *S1P0;
    ClickableLabel *S1P1;
    ClickableLabel *S1P2;
    ClickableLabel *S2P0;
    ClickableLabel *S2P1;
    ClickableLabel *S2P2;
    ClickableLabel *S3P0;
    ClickableLabel *S3P1;
    ClickableLabel *S3P2;
    ClickableLabel *S4P0;
    ClickableLabel *S4P1;
    ClickableLabel *S4P2;
    ClickableLabel *S5P0;
    ClickableLabel *S5P1;
    ClickableLabel *S5P2;
    ClickableLabel *S6P0;
    ClickableLabel *S6P1;
    ClickableLabel *S6P2;
    ClickableLabel *S7P0;
    ClickableLabel *S7P1;
    ClickableLabel *S7P2;
    ClickableLabel *S8P0;
    ClickableLabel *S8P1;
    ClickableLabel *S8P2;

    ClickableLabel *S1;
    ClickableLabel *S2;
    ClickableLabel *S3;
    ClickableLabel *S4;
    ClickableLabel *S5;
    ClickableLabel *S6;
    ClickableLabel *S7;
    ClickableLabel *S8;

    ClickableLabel *L1;
    ClickableLabel *L2;
    ClickableLabel *P1;
    ClickableLabel *P2;
    ClickableLabel *P3;
    ClickableLabel *P4;

    ClickableLabel *R1;
    ClickableLabel *R2;
    ClickableLabel *R3;
    ClickableLabel *R4;
    ClickableLabel *R5;

    QPushButton *ButtonDefektPlatz;
    QPushButton *ButtonDefektRobot;
    QPushButton *ButtonNotDefektPlatz;
    QPushButton *ButtonNotDefektRobot;
    QPushButton *ButtonFreeParkplatz;
    QPushButton *ButtonFreeStation;
    QPushButton *ButtonFreePlatz;
    QPushButton *ButtonBlockAuftrag;

    QList<QPushButton *> HardCodeButtons;

signals:
    void NeuerAuftrag(QVector<int> A);
    void NeuerProzess(Prozess *p);
    void EinhornLaden(QVector<double> p);
    void PauseClicked(bool pause);
    void DebugPressed();

    void AddS1P1();
    void AddS1P2();
    void RemoveS8P1();
    void RemoveS8P2();

    void GetTimestampsOnStationClicked(int id);
    void GetTimestampsOnProzessClicked(int id);

    void HardCodeStationsplatzStatus(int id, int status);
    void HardCodeStationStatus(int id, int status);
    void HardCodeParkplatzStatus(int id, int status);
    void HardCodeRobotDefekt(int id, bool defect);

public slots:
    void UpdateRobotino1Position(QVector<int> newPosition);
    void UpdateRobotino2Position(QVector<int> newPosition);
    void UpdateRobotino3Position(QVector<int> newPosition);
    void UpdateRobotino4Position(QVector<int> newPosition);
    void UpdateRobotino5Position(QVector<int> newPosition);

    void UpdateRobotinoPixmap(int RobotID);

    void UpdateRobotino1Akku(int percent);
    void UpdateRobotino2Akku(int percent);
    void UpdateRobotino3Akku(int percent);
    void UpdateRobotino4Akku(int percent);
    void UpdateRobotino5Akku(int percent);

    void UpdateRobotino1Greifer(bool status);
    void UpdateRobotino2Greifer(bool status);
    void UpdateRobotino3Greifer(bool status);
    void UpdateRobotino4Greifer(bool status);
    void UpdateRobotino5Greifer(bool status);

    void UpdateRobotino1Alive(bool alive);
    void UpdateRobotino2Alive(bool alive);
    void UpdateRobotino3Alive(bool alive);
    void UpdateRobotino4Alive(bool alive);
    void UpdateRobotino5Alive(bool alive);

    void UpdateRobotino1Hindernis(int hindernis);
    void UpdateRobotino2Hindernis(int hindernis);
    void UpdateRobotino3Hindernis(int hindernis);
    void UpdateRobotino4Hindernis(int hindernis);
    void UpdateRobotino5Hindernis(int hindernis);

    void UpdateStation(int ID, bool newState);
    void UpdateParkplatz(int ID, int newState);
    void UpdateStationsplatz(int ID, int newState);

    void UpdateProzessLabelTooltip(Prozess *p);
    void UpdateStationToolTip(int ID, QString temp);
    void SetTimestamps(QList<Timestamp*> timestamps);
    void AddAuftragsItem(Auftrag *a);
    void StationClicked(int id);
    void ParkplatzClicked(int id);
    void RobotClicked(int id);
    //void WerkstueckClicked(int id);

private slots:
    void on_sendAuftrag_clicked();
    void on_sendProzess_clicked();

    void on_S1P1dazu_clicked();
    void on_S1P2dazu_clicked();
    void on_S8P1weg_clicked();
    void on_S8P2weg_clicked();

    void on_debugButton1_clicked();

    void on_AuftragsListWidget_itemClicked(QListWidgetItem *item);

    void on_AuftragsListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_ButtonDefektPlatz_clicked(bool checked);
    void on_ButtonDefektRobot_clicked(bool checked);
    void on_ButtonNotDefektPlatz_clicked(bool checked);
    void on_ButtonNotDefektRobot_clicked(bool checked);
    void on_ButtonFreeParkplatz_clicked(bool checked);
    void on_ButtonFreeStation_clicked(bool checked);
    void on_ButtonFreePlatz_clicked(bool checked);
    void on_ButtonAuftragBlocked_clicked(bool checked);

    void on_pushButton_clicked();

    void on_Pause_clicked(bool checked);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *blinktimer;

    QTextEdit *DebugTextArea;

    QFrame *Robotino1;
    QFrame *Robotino2;
    QFrame *Robotino3;
    QFrame *Robotino4;
    QFrame *Robotino5;

    QListWidget *AuftragListWidget;

    QPushButton *AliveR1;
    QPushButton *AliveR2;
    QPushButton *AliveR3;
    QPushButton *AliveR4;
    QPushButton *AliveR5;

    QProgressBar *AkkuR1;
    QProgressBar *AkkuR2;
    QProgressBar *AkkuR3;
    QProgressBar *AkkuR4;
    QProgressBar *AkkuR5;

    QProgressBar *AkkukleinR1;
    QProgressBar *AkkukleinR2;
    QProgressBar *AkkukleinR3;
    QProgressBar *AkkukleinR4;
    QProgressBar *AkkukleinR5;

    bool G1 = false, G2 = false, G3 = false, G4 = false, G5 = false;
    bool D1 = false, D2 = false, D3 = false, D4 = false, D5 = false;
    bool A1 = false, A2 = false, A3 = false, A4 = false, A5 = false;
    bool toggler = false;
    int H1 = 0, H2 = 0, H3 = 0, H4 = 0, H5 = 0;
    QStringList WhatsThis = { "Auftragsitem", "Prozessitem", "Prozessschritt"};

    void UpdateRobotinoAlive(int RobotID, bool alive, QPushButton *P);
    void UpdateRobotinoAkku(int percent, QProgressBar *P, QProgressBar *Pklein);
    void ToggleAliveRobotino();
    void UpdateRobotinoXPixmap(QLabel *Rlabel, bool G, bool D, int H, bool einhorn);
    void UpdateRobotinoPosition(QVector<int> newPosition, QFrame *Robotino,  QLabel *Rlabel, bool G, bool D, int H, bool einhorn);
    void ResetButtonsExeptOne(QPushButton *b);
    QPushButton *GetPressedHardCodeButton();
};

#endif // MAINWINDOW_H
