#include "fertigungsplanung.h"
#include "mainwindow.h"

Fertigungsplanung::Fertigungsplanung(QObject *parent) : QObject(parent)
{
}

void Fertigungsplanung::InitProzesses()
{
    Prozessliste = db->GetAllExistingProzesses();

    if (Prozessliste.length() < 5)
    {
        Prozessliste.clear();

        Prozess *p1 = new Prozess();
        p1->referenzId = 1;
        p1->Prozessschritte.append(new Prozessschritt(6, 20));
        p1->Prozessschritte.append(new Prozessschritt(2, 10));
        p1->Prozessschritte.append(new Prozessschritt(4, 30));
        p1->Prozessschritte.append(new Prozessschritt(8, 2));

        Prozessliste.append(p1);
        emit ProzessAdded(p1);
        emit DebugAreaString("Prozess hinzugefügt");

        Prozess *p2 = new Prozess();
        p2->referenzId = 2;
        p2->Prozessschritte.append(new Prozessschritt(4, 15));
        p2->Prozessschritte.append(new Prozessschritt(6, 20));
        p2->Prozessschritte.append(new Prozessschritt(8, 2));

        Prozessliste.append(p2);
        emit ProzessAdded(p2);
        emit DebugAreaString("Prozess hinzugefügt");

        Prozess *p3 = new Prozess();
        p3->referenzId = 3;
        p3->Prozessschritte.append(new Prozessschritt(3, 45));
        p3->Prozessschritte.append(new Prozessschritt(8, 2));

        Prozessliste.append(p3);
        emit ProzessAdded(p3);
        emit DebugAreaString("Prozess hinzugefügt");

        Prozess *p4 = new Prozess();
        p4->referenzId = 4;
        p4->Prozessschritte.append(new Prozessschritt(5, 35));
        p4->Prozessschritte.append(new Prozessschritt(7, 15));
        p4->Prozessschritte.append(new Prozessschritt(3, 20));
        p4->Prozessschritte.append(new Prozessschritt(5, 10));
        p4->Prozessschritte.append(new Prozessschritt(2, 15));
        p4->Prozessschritte.append(new Prozessschritt(8, 2));

        Prozessliste.append(p4);
        emit ProzessAdded(p4);
        emit DebugAreaString("Prozess hinzugefügt");

        Prozess *p5 = new Prozess();
        p5->referenzId = 5;
        p5->Prozessschritte.append(new Prozessschritt(2, 10));
        p5->Prozessschritte.append(new Prozessschritt(7, 20));
        p5->Prozessschritte.append(new Prozessschritt(5, 30));
        p5->Prozessschritte.append(new Prozessschritt(8, 2));

        Prozessliste.append(p5);
        emit ProzessAdded(p5);
        emit DebugAreaString("Prozess hinzugefügt");

    }
    else
    {
        foreach (Prozess *prozessitem, Prozessliste )
        {
            emit ProzessAdded(prozessitem);
        }
    }

}

void Fertigungsplanung::Start()
{
    StateMachine.setInitialState(StateCheckRobots);
    StateMachine.start();
    emit DebugAreaString("Fertigungsplanung gestartet");
}

void Fertigungsplanung::AddAuftrag(QVector<int> Avalues)
{

    Auftrag *A = new Auftrag();

    int nextID = db->GetNextLfdId();

    for (int prozesscounter = 0; prozesscounter < 5; prozesscounter++) //5 Prozess UI Elemente
    {
        for (int i = 0; i < Avalues[prozesscounter]; i++) //Anzahl der eingegebenen Prozesszahl
        {
            if (Prozessliste.size() >= prozesscounter+1){
                Prozess *p = new Prozess();
                p->referenzId = Prozessliste.at(prozesscounter)->referenzId;
                p->lfdId = nextID;
                nextID++;
                // Connect every prozess with all child prozesssteps
                for (int j = 0; j < Prozessliste.at(prozesscounter)->Prozessschritte.size(); j++)
                {
                    p->Prozessschritte.append(new Prozessschritt(Prozessliste.at(prozesscounter)->Prozessschritte.at(j)->Station(), Prozessliste.at(prozesscounter)->Prozessschritte.at(j)->Dauer()));
                    QObject::connect(p->Prozessschritte.at(j), &Prozessschritt::FortschrittUpdated, p, &Prozess::UpdateFortschritt);
                }
                A->Prozesse.append(p);
                QObject::connect(p, &Prozess::FortschrittUpdated, A, &Auftrag::UpdateFortschritt);
                QObject::connect(p, &Prozess::ProzessFinished, this, &Fertigungsplanung::StationReady);
            }
        }
    }
    if (!A->Prozesse.empty())
    {
        A->id = Auftragsliste.length()+1;
        Auftragsliste.append(A);
        emit AuftragAdded(A);
        emit DebugAreaString("Auftrag hinzugefügt");
    }
}

void Fertigungsplanung::AddProzess(Prozess *P)
{
    Prozessliste.append(P);
    emit ProzessAdded(P);
    emit DebugAreaString("Prozess hinzugefügt");
}

void Fertigungsplanung::StationReady(int prozessID)
{
    int station = db->GetWerkstueckPosition(prozessID);
    if (Fs.GetStationPlatzByID(station) != nullptr)
    {
        Fs.GetStationPlatzByID(station)->setFullReady();
    }
    else
    {
        DebugAreaString("ERROR: Could not set Station Place ready after Prozess Timer elapsed");
    }
}

void Fertigungsplanung::UpdateRobotino1Greifer(bool greifer){OnRobotGreiferChanged(1, greifer);}
void Fertigungsplanung::UpdateRobotino2Greifer(bool greifer){OnRobotGreiferChanged(2, greifer);}
void Fertigungsplanung::UpdateRobotino3Greifer(bool greifer){OnRobotGreiferChanged(3, greifer);}
void Fertigungsplanung::UpdateRobotino4Greifer(bool greifer){OnRobotGreiferChanged(4, greifer);}

void Fertigungsplanung::OnRobotGreiferChanged(int robotID, bool greifer)
{
    Robotino *r;
    switch (robotID) {
    case 1:
        r = r1;
        break;
    case 2:
        r = r2;
        break;
    case 3:
        r = r3;
        break;
    case 4:
        r = r4;
        break;
    default:
        r = r1; //TODO gefährlich
        break;
    }

    // if greifer opened, so a prozess is ready
    if (!greifer)
    {
        int prozessid = db->GetRobotWerkstueck(robotID);
        if (prozessid != -1)
        {
            db->UpdateRobotWerkstueck(robotID,0);
            foreach (Auftrag *item, Auftragsliste)
            {
                Prozess * p = item->GetProzessByID(prozessid);
                if (p == nullptr)
                {
                    continue;
                }
                p->SetProgressTrue();
                p->StartTimer(p->GetNextUnfinishedProzessstep()->Dauer());
                int station = db->GetWerkstueckPosition(prozessid);
                if (Fs.GetStationPlatzByID(station) != nullptr)
                {
                    Fs.GetStationPlatzByID(station)->setFull();
                }
                else
                {
                    DebugAreaString("ERROR: Could not set Station Place full after Greifer opened");
                }
                //emit UpdateStationToolTip(station, "Werkstueck: " + QString::number(prozessid));
            }
        }
    }
    else
    //Greifer closed, so a prozess is started
    {
        //Startpunkt freigeben
        db->UpdateArbeitsplatz(-1, 0, r->Position());
        emit StationChanged(r->Position(), true);
        db->UpdateStationPlaceStatus(r->Position(), 0);

        if (Fs.GetStationPlatzByID(r->Position()) != nullptr)
        {
            Fs.GetStationPlatzByID(r->Position())->setFree();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Source Station Place free after Robot Greifer closed");
        }
        emit UpdateStationToolTip(r->Position(), "");
    }
}

void Fertigungsplanung::UpdateRobotino1Status(int status, int pos1, int pos2){OnRobotStatusChanged(1, status, pos1, pos2);}
void Fertigungsplanung::UpdateRobotino2Status(int status, int pos1, int pos2){OnRobotStatusChanged(2, status, pos1, pos2);}
void Fertigungsplanung::UpdateRobotino3Status(int status, int pos1, int pos2){OnRobotStatusChanged(3, status, pos1, pos2);}
void Fertigungsplanung::UpdateRobotino4Status(int status, int pos1, int pos2){OnRobotStatusChanged(4, status, pos1, pos2);}


void Fertigungsplanung::OnRobotStatusChanged(int robotID, int status, int pos1, int pos2)
{
    Q_UNUSED(pos1);
    Q_UNUSED(pos2);

    Robotino *r;
    switch (robotID) {
    case 1:
        r = r1;
        break;
    case 2:
        r = r2;
        break;
    case 3:
        r = r3;
        break;
    case 4:
        r = r4;
        break;
    default:
        r = r1; //TODO gefährlich
        break;
    }


    // Startposition Freigeben
    if (status == 1)
    {
        if (r->Position() != -1)
        {
            if (r->Position()/10 == 0) //Parkplatz
            {
                db->UpdateParkplatz(r->Position()%10, 0, 0);
                if (Fs.GetPlatzByID(static_cast<int>(r->Position())) != nullptr)
                {
                    Fs.GetPlatzByID(static_cast<int>(r->Position()))->setFree();
                }
                else
                {
                    DebugAreaString("ERROR: Could not set Loading Station Place free after Robot drove away");
                }
            }
            else //Arbeitsplatz
            {
                db->UpdateArbeitsplatz(0, -1, r->Position());
                emit StationChanged(r->Position(), true);
                db->UpdateStationPlaceStatus(r->Position(), 0);
//                if (Fs.GetStationPlatzByID(static_cast<int>(r->Position())) != nullptr)
//                {
//                    Fs.GetStationPlatzByID(static_cast<int>(r->Position()))->setFree();
//                }
//                else
//                {
//                    DebugAreaString("ERROR: Could not set Target Station Place free after Robot drove away");
//                }
            }
        }
    }
}

void Fertigungsplanung::RobotErrorOccured(int robotID, int errorID)
{
    if (errorID == 2)
    {
        emit DebugAreaString("ROBOT_ERROR: Robot " + QString::number(robotID) + " lost Werkstueck");
        //TODO Auftrag blockieren
    }
    if (errorID == 3)
    {
        emit DebugAreaString("ROBOT_ERROR: Robot " + QString::number(robotID) + " was not able to grab Werkstueck");
        //TODO Auftrag blockieren
    }
    else if (errorID == 4)
    {
        emit DebugAreaString("ROBOT_ERROR: Robot " + QString::number(robotID) + " was not able to plan Route");
        //TODO Robot defekt? - Sonderfälle betrachten...
    }
}

void Fertigungsplanung::UpdatePause(bool pause)
{
    this->pause = pause;
}

void Fertigungsplanung::OnStationClickedNormal(int id)
{
    int temp = db->GetWerkstueckOnStation(id);
    if (temp > 0)
    {
        emit WerkstueckClicked(temp);
    }
    else
    {
        id /= 10;
        id *= 10;
        emit StationClicked(id);
    }
    //WriteToDebugTextArea("Angeklicked!!! " + QString::number(id));
    //emit GetTimestampsOfStation(id);

}

#define UPDATE HARD ROBOT {

void Fertigungsplanung::UpdateHardRobotDefect(int id, bool defect)
{
    Robotino *r = nullptr;

    switch (id) {
    case 1:
        r = r1;
        break;
    case 2:
        r = r2;
        break;
    case 3:
        r = r3;
        break;
    case 4:
        r = r4;
        break;
    default:
        DebugAreaString("ERROR: Robot not found");
        break;
    }

    if (r != nullptr)
    {
        r->setDefect(defect);
        emit UpdateRobotinoPixmap(id);
        r->Defect() ? DebugAreaString("Warning: Robot " + QString::number(r->ID()) + " exploded") : DebugAreaString("Info: Robot " + QString::number(r->ID()) + " repaired");
        //TODO Roboter werkstück freigeben?! prozess freigeben?
        //Zielstation frei, Startstationsplatz frei, Station freigeben ?
    }
}

void Fertigungsplanung::UpdateHardStationStatus(int id, int status)
{
    if (status == 0)
    {
        id /= 10;
        id *= 10;

        emit StationChanged(id, true);
        db->UpdateArbeitsplatz(0, -1, id);
        db->UpdateArbeitsplatz(0, -1, id+1);
        db->UpdateArbeitsplatz(0, -1, id+2);
    }
}

void Fertigungsplanung::UpdateHardStationsplatzStatus(int id, int status)
{
    if (status == 0)
    {
        db->UpdateArbeitsplatz(-1, 0,  id);
        if (Fs.GetStationPlatzByID(id) != nullptr)
        {
            Fs.GetStationPlatzByID(id)->setFree();
            emit UpdateStationToolTip(id, "");

        }
        else
        {
            DebugAreaString("ERROR: Could not set Station place free from Hard Coding Button");
        }
    }
    else if (status == 4)
    {
        if (Fs.GetStationPlatzByID(id) != nullptr)
        {
            Fs.GetStationPlatzByID(id)->setDefect();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Station place defect from Hard Coding Button");
        }
    }

//    db->UpdateArbeitsplatz(0, -1, id);
//    emit StationChanged(static_cast<int>(positionSendData->data()[1]), false);
}

void Fertigungsplanung::UpdateHardParkplatzStatus(int id, int status)
{
    if (status == 0)
    {
        db->UpdateParkplatz(id,0,0);

        if (Fs.GetPlatzByID(id) != nullptr)
        {
            Fs.GetPlatzByID(id)->setFree();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Station free from Hard Coding Button");
        }
    }
}

#define ENDREGION }

#define STATEMACHINE {


void Fertigungsplanung::AddStatesToStateMachine()
{
    StateMachine.addState(StateWait);
    StateMachine.addState(StateSendLoadingTaskWait);
    StateMachine.addState(StateSendPositionTaskWait);
    StateMachine.addState(StateSendParkingTaskWait);
    StateMachine.addState(StateCheckRobots);
    StateMachine.addState(StateCheckAkku);
    StateMachine.addState(StateCheckAuftrag);
    StateMachine.addState(StateCheckParkplatzRobots);
    StateMachine.addState(StateSendLoadingTask);
    StateMachine.addState(StateSendPositionTask);
    StateMachine.addState(StateSendParkingTask);
    StateMachine.addState(StateSendTimeout);
}

void Fertigungsplanung::AddTransitionsToStates()
{
    StateCheckRobots->addTransition(this, SIGNAL(nextState()), StateCheckAkku);
    StateCheckRobots->addTransition(this, SIGNAL(nextState2()), StateCheckParkplatzRobots);
    StateCheckParkplatzRobots->addTransition(this, SIGNAL(nextState2()), StateWait);
    StateCheckParkplatzRobots->addTransition(this, SIGNAL(nextState()), StateCheckAkku);
    StateWait->addTransition(timer, SIGNAL(timeout()), StateCheckRobots);
    StateCheckAkku->addTransition(this, SIGNAL(nextState()), StateCheckAuftrag);
    StateCheckAkku->addTransition(this, SIGNAL(nextState2()), StateSendLoadingTask);
    StateCheckAkku->addTransition(this, SIGNAL(nextState3()), StateWait);
    StateSendLoadingTask->addTransition(this, SIGNAL(nextState()), StateSendLoadingTaskWait);
    StateSendLoadingTaskWait->addTransition(sendtimer, SIGNAL(timeout()), StateSendLoadingTask);
    StateSendLoadingTask->addTransition(sendtimeout, SIGNAL(timeout()), StateSendTimeout);
    StateSendLoadingTaskWait->addTransition(sendtimeout, SIGNAL(timeout()), StateSendTimeout);
    StateSendLoadingTask->addTransition(this, SIGNAL(nextState2()), StateCheckRobots);
    StateCheckAuftrag->addTransition(this, SIGNAL(nextState()), StateSendPositionTask);
    StateCheckAuftrag->addTransition(this, SIGNAL(nextState3()), StateSendParkingTask);
    StateCheckAuftrag->addTransition(this, SIGNAL(nextState2()), StateWait);
    StateSendPositionTask->addTransition(this, SIGNAL(nextState()), StateSendPositionTaskWait);
    StateSendPositionTask->addTransition(this, SIGNAL(nextState2()), StateCheckRobots);
    StateSendPositionTaskWait->addTransition(sendtimer, SIGNAL(timeout()), StateSendPositionTask);
    StateSendPositionTask->addTransition(sendtimeout, SIGNAL(timeout()), StateSendTimeout);
    StateSendPositionTaskWait->addTransition(sendtimeout, SIGNAL(timeout()), StateSendTimeout);
    StateSendParkingTask->addTransition(this, SIGNAL(nextState()), StateSendParkingTaskWait);
    StateSendParkingTask->addTransition(this, SIGNAL(nextState2()), StateCheckRobots);
    StateSendParkingTaskWait->addTransition(sendtimer, SIGNAL(timeout()), StateSendParkingTask);
    StateSendParkingTask->addTransition(sendtimeout, SIGNAL(timeout()), StateSendTimeout);
    StateSendParkingTaskWait->addTransition(sendtimeout, SIGNAL(timeout()), StateSendTimeout);
    StateSendTimeout->addTransition(this, SIGNAL(nextState()), StateCheckRobots);
}

void Fertigungsplanung::Wait()
{
//        QObject::connect(timer, &QTimer::timeout, &robot3, &Robotino::PrintPosition);
        timer->start(2000);
}

void Fertigungsplanung::SendLoadingTaskWait()
{
//        QObject::connect(timer, &QTimer::timeout, &robot3, &Robotino::PrintPosition);
        sendtimer->start(700);
}

void Fertigungsplanung::SendPositionTaskWait()
{
//        QObject::connect(timer, &QTimer::timeout, &robot3, &Robotino::PrintPosition);
        sendtimer->start(700);
}

void Fertigungsplanung::SendParkingTaskWait()
{
//        QObject::connect(timer, &QTimer::timeout, &robot3, &Robotino::PrintPosition);
        sendtimer->start(700);
}

void Fertigungsplanung::CheckRobots()
{
    QList<Robotino*> RobotList = {r1, r2, r3, r4};
    QList<UdpHandler*> RobotUDPList = {r1UDP, r2UDP, r3UDP, r4UDP};

    QList<int>random = GetShuffeled1To4();

    if (RobotList[random.at(0) - 1]->Status() == 0 && !RobotList[random.at(0) - 1]->Defect() && RobotList[random.at(0) - 1]->Alive())
    {
        usedRobot = RobotList[random.at(0) - 1];
        usedUDP = RobotUDPList[random.at(0) - 1];
        emit nextState();
    }
    else if (RobotList[random.at(1) - 1]->Status() == 0 && !RobotList[random.at(1) - 1]->Defect() && RobotList[random.at(1) - 1]->Alive())
    {
        usedRobot = RobotList[random.at(1) - 1];
        usedUDP = RobotUDPList[random.at(1) - 1];
        emit nextState();
    }
    else if (RobotList[random.at(2) - 1]->Status() == 0 && !RobotList[random.at(2) - 1]->Defect() && RobotList[random.at(2) - 1]->Alive())
    {
        usedRobot = RobotList[random.at(2) - 1];
        usedUDP = RobotUDPList[random.at(2) - 1];
        emit nextState();
    }
    else if (RobotList[random.at(3) - 1]->Status() == 0 && !RobotList[random.at(3) - 1]->Defect() && RobotList[random.at(3) - 1]->Alive())
    {
        usedRobot = RobotList[random.at(3) - 1];
        usedUDP = RobotUDPList[random.at(3) - 1];
        emit nextState();
    }
    else
    {
        emit nextState2();
    }
}

void Fertigungsplanung::CheckParkplatzRobots()
{
    QList<Robotino*> RobotList = {r1, r2, r3, r4};
    QList<UdpHandler*> RobotUDPList = {r1UDP, r2UDP, r3UDP, r4UDP};

    QList<int>random = GetShuffeled1To4();

    if (RobotList[random.at(0) - 1]->Status() >= 201 && RobotList[random.at(0) - 1]->Status() <= 204 && !RobotList[random.at(0) - 1]->Defect())
    {
        usedRobot = RobotList[random.at(0) - 1];
        usedUDP = RobotUDPList[random.at(0) - 1];
        emit nextState();
    }
    else if (RobotList[random.at(1) - 1]->Status() >= 201 && RobotList[random.at(1) - 1]->Status() <= 204 && !RobotList[random.at(1) - 1]->Defect())
    {
        usedRobot = RobotList[random.at(1) - 1];
        usedUDP = RobotUDPList[random.at(1) - 1];
        emit nextState();
    }
    else if (RobotList[random.at(2) - 1]->Status() >= 201 && RobotList[random.at(2) - 1]->Status() <= 204 && !RobotList[random.at(2) - 1]->Defect())
    {
        usedRobot = RobotList[random.at(2) - 1];
        usedUDP = RobotUDPList[random.at(2) - 1];
        emit nextState();
    }
    else if (RobotList[random.at(3) - 1]->Status() >= 201 && RobotList[random.at(3) - 1]->Status() <= 204 && !RobotList[random.at(3) - 1]->Defect())
    {
        usedRobot = RobotList[random.at(3) - 1];
        usedUDP = RobotUDPList[random.at(3) - 1];
        emit nextState();
    }
    else
    {
        emit nextState2();
    }

}


void Fertigungsplanung::CheckAkku()
{
    if (usedRobot->Akku() < 25)
    {
        int ladeid = db->GetFreeLadestation();
        if (ladeid != 0)
        {
            positionSendData->clear();
            positionSendData->resize(5);
            positionSendData->data()[0] = 3;
            positionSendData->data()[1] = ladeid;
            positionSendData->data()[2] = 0;
            positionSendData->data()[3] = 0;
            positionSendData->data()[4] = 0;

            emit nextState2();
        }
        else
        {
            // Roboter Ladestation belegt, roboter tut nix und wartet
            emit nextState3();
        }
    }
    else
    {
        emit nextState();
    }
}

void Fertigungsplanung::CheckAuftrag()
{
    //QList<Prozessschritt *> unfinishedList;
    QList<Prozess *> unfinishedProzessList;
    usedProzessstep = nullptr;
    usedProzess = nullptr;
    bool sendet = false;

    foreach(Auftrag *item, Auftragsliste)
    {
        //unfinishedList.append(item->GetNextUnfinishedProzesssteps());
        unfinishedProzessList.append(item->GetAllUnfinishedProzesses());
    }


    positionSendData->clear();
    positionSendData->resize(5);
    positionSendData->data()[0] = 1;

    for (int i = 0; i < unfinishedProzessList.size(); i++)
    {
        if (pause)
        {
            break;
        }

        positionSendData->data()[1] = 0;
        positionSendData->data()[2] = 0;
        positionSendData->data()[3] = 0;
        positionSendData->data()[4] = 0;

        usedProzess = unfinishedProzessList.at(i);
        usedProzessstep = usedProzess->GetNextUnfinishedProzessstep();

        // CHECK CONDITIONS

        // Prozess is running at Station
        if (usedProzess->InProgress())
        {
            continue;
        }

        // First Prozessstep of Prozess
        if (usedProzess->GetActualProzessstep() == nullptr)
        {
            // Startstation Roboter frei (nicht reserviert/nicht belegt)?
            if (db->IsStationRobotFree(1))
            {
                //Is Werkstück in Lager
                if (db->GetLagerWerkstueck() > 0)
                {
                    positionSendData->data()[1] = 10 + db->GetLagerWerkstueck();
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
        else // second etc. Step in Progress
        {
            // Startstation Roboter frei (nicht reserviert/nicht belegt)?
            if (db->IsStationRobotFree(usedProzess->GetActualProzessstep()->Station()))
            {
                positionSendData->data()[1] = db->GetWerkstueckPosition(usedProzess->lfdId);
            }
            else
            {
                continue;
            }
        }

        // Zielstation Robot free (nicht reserviert/nicht belegt)?
        if (!db->IsStationRobotFree(usedProzessstep->Station()))
        {
            continue;
        }
        // Zielposition frei (eine der beiden)?
        if (db->GetZielStationsplatzFree(usedProzessstep->Station()) > 0)
        {
            positionSendData->data()[2] = usedProzessstep->Station()*10 + db->GetZielStationsplatzFree(usedProzessstep->Station());
        }
        else
        {
            continue;
        }

        //Send to Robotino
        emit nextState();
        sendet = true;
        break;
    }

    if (!sendet) //kein auftrag vorhanden oder Auftragssenden blockiert
    {
        if (usedRobot->Status() >= 201 && usedRobot->Status() <= 204)
        {
            //roboter parkt bereits, back to start
            emit nextState2();
        }
        else //schick roboter parken
        {
            positionSendData->data()[0] = 2;
            positionSendData->data()[1] = db->GetNextFreeParkplatz();
            positionSendData->data()[2] = 0;
            positionSendData->data()[3] = 0;
            positionSendData->data()[4] = 0;

            emit nextState3();
        }
    }

//    emit nextState2();
}

void Fertigungsplanung::SendTimeout()
{
//TODO Roboter tot schalten?
    emit nextState();
}

void Fertigungsplanung::SendLoadingTask()
{
    if (usedRobot->Status() == 0 || (db->IsRobotOnParkplatz(usedRobot->ID()) && usedRobot->Status() > 200))
    {
        if (!sendtimeout->isActive())
        {
            sendtimeout->start(25000);
        }
        usedUDP->WriteData(*positionSendData);

        emit nextState();
    }
    else
    {
        sendtimeout->stop();
        emit DebugAreaString("Action: Robotino " + QString::number(usedRobot->ID()) + " move to LoadingStation: " + QString::number(static_cast<int>(positionSendData->at(1))) );
        emit nextState2();

        //Update Zielstation reserved
        db->UpdateParkplatz(static_cast<int>(positionSendData->at(1)),1,usedRobot->ID());

        if (Fs.GetPlatzByID(static_cast<int>(positionSendData->data()[1])) != nullptr)
        {
            Fs.GetPlatzByID(static_cast<int>(positionSendData->data()[1]))->setReserved();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Loading Station Place reserved after sending Task to Robot");
        }
    }
}

void Fertigungsplanung::SendParkingTask()
{
    if (usedRobot->Status() == 0 || (db->IsRobotOnParkplatz(usedRobot->ID()) && usedRobot->Status() > 200))
    {
        if (!sendtimeout->isActive())
        {
            sendtimeout->start(25000);
        }

        usedUDP->WriteData(*positionSendData);

        emit nextState();
    }
    else
    {
        sendtimeout->stop();
        emit DebugAreaString("Action: Robotino " + QString::number(usedRobot->ID()) + " move to ParkingStation: " + QString::number(static_cast<int>(positionSendData->at(1))) );
        emit nextState2();
        //Update Zielstation reserved
        db->UpdateParkplatz(static_cast<int>(positionSendData->at(1)),1,usedRobot->ID());


        if (Fs.GetPlatzByID(static_cast<int>(positionSendData->data()[1])) != nullptr)
        {
            Fs.GetPlatzByID(static_cast<int>(positionSendData->data()[1]))->setReserved();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Parking Station Place reserved after sending Task to Robot");
        }
    }
}


void Fertigungsplanung::SendPositionTask()
{
    if (usedRobot->Status() == 0 || (db->IsRobotOnParkplatz(usedRobot->ID()) && usedRobot->Status() > 200))
    {
        if (!sendtimeout->isActive())
        {
            sendtimeout->start(25000);
        }

        usedUDP->WriteData(*positionSendData);

        emit nextState();
    }
    else //Sucsessfully Send!
    {

        sendtimeout->stop();
        // StartArbeitsplatz updaten
        db->UpdateArbeitsplatz(usedRobot->ID(), 0, static_cast<int>(positionSendData->data()[1]));
        emit StationChanged(static_cast<int>(positionSendData->data()[1]), false);
        // ZielArbeitsplatz updaten
        db->UpdateArbeitsplatz(usedRobot->ID(), usedProzess->lfdId, static_cast<int>(positionSendData->data()[2]));
        emit StationChanged(static_cast<int>(positionSendData->data()[2]), false);
        // Robot Werkstueck updaten
        db->UpdateRobotWerkstueck(usedRobot->ID(), usedProzess->lfdId);
        //Update RFID if first station
        if (positionSendData->data()[1] >= 10 && positionSendData->data()[1] <= 12)
        {
            db->UpdateRFIDWrite(usedProzess->lfdId);
        }

        // Update Targetposition

        if (Fs.GetStationPlatzByID(static_cast<int>(positionSendData->data()[2])) != nullptr)
        {
            Fs.GetStationPlatzByID(static_cast<int>(positionSendData->data()[2]))->setReserved();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Target Station Place reserved after sending Task to Robot");
        }

        emit UpdateStationToolTip(static_cast<int>(positionSendData->data()[2]), "Werkstueck: " + QString::number(usedProzess->lfdId));

        // Update Sourceposition

        if (Fs.GetStationPlatzByID(static_cast<int>(positionSendData->data()[1])) != nullptr)
        {
            Fs.GetStationPlatzByID(static_cast<int>(positionSendData->data()[1]))->setReserved();
        }
        else
        {
            DebugAreaString("ERROR: Could not set Source Station Place reserved after sending Task to Robot");
        }

        emit UpdateStationToolTip(static_cast<int>(positionSendData->data()[1]), "Werkstueck: " + QString::number(usedProzess->lfdId));

        emit DebugAreaString("Action: Robot " + QString::number(usedRobot->ID()) + " move WS " + QString::number(usedProzess->lfdId) + " from P " + QString::number(static_cast<int>(positionSendData->at(1))) + " to P: " + QString::number(static_cast<int>(positionSendData->at(2))) );
        emit nextState2();
    }
}

#define ENDREGION }

QList<int> Fertigungsplanung::GetShuffeled1To4()
{
    QList<int> liste;
    int i = QRandomGenerator::global()->bounded(1, 5);
    liste.append(i);
    i = QRandomGenerator::global()->bounded(1, 4);
    (liste.contains(i)) ? liste.append(i+1) : liste.append(i);
    i = QRandomGenerator::global()->bounded(1, 3);
    if (liste.contains(i))
    {
        if (liste.contains(i+1))
        {
            liste.append(i+2);
        }
        else
        {
            liste.append(i+1);
        }
    }
    else
    {
        liste.append(i);
    }

    if (!liste.contains(1)) {liste.append(1);}
    else if (!liste.contains(2)) {liste.append(2);}
    else if (!liste.contains(3)) {liste.append(3);}
    else if (!liste.contains(4)) {liste.append(4);}
    return liste;
}

void Fertigungsplanung::DebugSlot()
{
    QList<Prozessschritt *> unfinishedList;
    foreach(Auftrag *item, Auftragsliste)
    {
        unfinishedList.append(item->GetNextUnfinishedProzesssteps());
    }

    if (unfinishedList.length() > 0)
    {
        int k = unfinishedList.length();
        unfinishedList.at(QRandomGenerator::global()->bounded(0, k))->SetFortschrittReady();
    }
}
