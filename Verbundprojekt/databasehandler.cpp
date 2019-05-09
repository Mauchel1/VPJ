#include "databasehandler.h"

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.0.107");
    db.setPort(3306);
    db.setDatabaseName("vpj");
    db.setUserName("FP");
    db.setPassword("1234");

    //    C:\Program Files\MySQL\MySQL Connector.C 6.1\lib
    bool ok = db.open();

//    Q_ASSERT(ok);
    Q_UNUSED(ok);

    QSqlError err;
    if (err.type() != QSqlError::NoError){
        qCritical() << err.text();
    }
}

void DatabaseHandler::InitDB()
{
    QSqlQuery query(db);
    SendOverQuary(query, "DELETE FROM vpj.rfid_timestamp;");
    SendOverQuary(query, "UPDATE vpj.roboter SET betriebsstatus=0, Werkstueck_RFID_Werkstueck=NULL;");
    SendOverQuary(query, "UPDATE vpj.parkplatz SET Status=0, Roboter_id_Roboter=NULL;");
    SendOverQuary(query, "UPDATE vpj.arbeitsplatz SET Status=0, Roboter_id_Roboter=NULL, Werkstueck_RFID_Werkstueck=NULL;");
    SendOverQuary(query, "UPDATE vpj.taggen SET Werkstueck_RFID_Werkstueck=NULL WHERE id_taggen=1;");
    SendOverQuary(query, "DELETE FROM vpj.werkstueck;");
    SendOverQuary(query, "DELETE FROM vpj.auftrag;");
}

// ------------GETTER------------ //

int DatabaseHandler::GetLagerWerkstueck()
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @Station1 =10;");
    SendOverQuary(query, "SELECT (case when (SUM(id_Arbeitsplatz))=@Station1+1+@Station1+2 then 1 when(SUM(id_Arbeitsplatz))=@Station1+1 then 1 when(SUM(id_Arbeitsplatz))=@Station1+2 then 2 else 0 end) FROM vpj.arbeitsplatz WHERE (id_Arbeitsplatz in (@Station1+1,@Station1+2) AND Status=3);");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

int DatabaseHandler::GetZielStationsplatzFree(int station)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @Station1 =" + QString::number(station*10) + ";");
    SendOverQuary(query, "SELECT (case when (SUM(id_Arbeitsplatz))=@Station1+1+@Station1+2 then 1 when(SUM(id_Arbeitsplatz))=@Station1+1 then 1 when(SUM(id_Arbeitsplatz))=@Station1+2 then 2 else 0 end) FROM vpj.arbeitsplatz WHERE (id_Arbeitsplatz in (@Station1+1,@Station1+2) AND Werkstueck_RFID_Werkstueck is NULL AND Status < 1);");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

bool DatabaseHandler::IsStationRobotFree(int station)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @Station1 =" + QString::number(station*10) + ";");
    SendOverQuary(query, "(SELECT (case when (SUM(Roboter_id_Roboter)>0) then 1 else 0 end) FROM vpj.arbeitsplatz WHERE id_Arbeitsplatz in (@Station1,@Station1+1,@Station1+2));");
    if (query.next()) {
        return query.value(0) == 0 ? true : false;
    }
    return false;
}

QList<Prozess*> DatabaseHandler::GetAllExistingProzesses()
{
    QSqlQuery query(db);
    SendOverQuary(query, "SELECT * FROM vpj.produktionsprozess;");
    QList<Prozess*> prozesslist;

    while (query.next()) { //TODO Prozesslänge soll irrelevant werden
        Prozess *p = new Prozess();
        p->referenzId = query.value(0).toInt();
        int station = query.value(1).toInt();
        int dauer = query.value(2).toInt();
        if (station == 0){prozesslist.append(p); continue;}
        p->Prozessschritte.append(new Prozessschritt(station, dauer));
        station = query.value(3).toInt();
        dauer = query.value(4).toInt();
        if (station == 0){prozesslist.append(p); continue;}
        p->Prozessschritte.append(new Prozessschritt(station, dauer));
        station = query.value(5).toInt();
        dauer = query.value(6).toInt();
        if (station == 0){prozesslist.append(p); continue;}
        p->Prozessschritte.append(new Prozessschritt(station, dauer));
        station = query.value(7).toInt();
        dauer = query.value(8).toInt();
        if (station == 0){prozesslist.append(p); continue;}
        p->Prozessschritte.append(new Prozessschritt(station, dauer));
        station = query.value(9).toInt();
        dauer = query.value(10).toInt();
        if (station == 0){prozesslist.append(p); continue;}
        p->Prozessschritte.append(new Prozessschritt(station, dauer));
        station = query.value(11).toInt();
        dauer = query.value(12).toInt();
        if (station == 0){prozesslist.append(p); continue;}
        p->Prozessschritte.append(new Prozessschritt(station, dauer));
        prozesslist.append(p);
    }

    return prozesslist;
}

int DatabaseHandler::GetNextFreeParkplatz()
{
    QSqlQuery query(db);
    SendOverQuary(query, "SELECT MIN(id_Parkplatz) FROM vpj.parkplatz WHERE Status=0;");
    if (query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

int DatabaseHandler::GetWerkstueckOnStation(int station)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @station=" + QString::number(station) + ";");
    SendOverQuary(query, "SELECT Werkstueck_RFID_Werkstueck FROM vpj.Arbeitsplatz WHERE id_Arbeitsplatz=@station;");
    if (query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

int DatabaseHandler::GetRobotWerkstueck(int robot)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @robo=" + QString::number(robot) + ";");
    SendOverQuary(query, "SELECT Werkstueck_RFID_Werkstueck FROM vpj.roboter WHERE id_Roboter=@robo;");
    if (query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

int DatabaseHandler::GetWerkstueckPosition(int werkstueck)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @werkstueck=" + QString::number(werkstueck) + ";");
    SendOverQuary(query, "SELECT id_Arbeitsplatz FROM vpj.Arbeitsplatz WHERE Werkstueck_RFID_Werkstueck=@werkstueck;");
    if (query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}


bool DatabaseHandler::IsRobotOnParkplatz(int robot)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @robo=" + QString::number(robot) + ";");
    SendOverQuary(query, "SELECT COUNT(*) FROM vpj.parkplatz WHERE Roboter_id_Roboter=@robo AND id_parkplatz<5;");

    if (query.next())
    {
        return query.value(0).toBool();
    }
    return false;
}

int DatabaseHandler::GetFreeLadestation()
{
    QSqlQuery query(db);
    //SendOverQuary(query, "SET @robo=" + QString::number(robot) + ";");
    SendOverQuary(query, "SELECT MIN(id_parkplatz) FROM vpj.parkplatz WHERE Roboter_id_Roboter is NULL AND id_parkplatz>4;");

    if (query.next())
    {
        return query.value(0).toInt();
    }
    return -1;
}

void DatabaseHandler::GetTimeStampsOfWerkstueck(int werkstueck)
{
    QList<Timestamp*> t;

    QSqlQuery query(db);
    SendOverQuary(query, "SET @Werkstueck=" + QString::number(werkstueck) + ";");
    SendOverQuary(query, "SELECT * FROM vpj.rfid_timestamp WHERE Werkstueck_RFID_Werkstueck=@Werkstueck;");
    QList<Prozess*> prozesslist;

    while (query.next()) {
        t.append(new Timestamp(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toUInt(), query.value(4).toInt()));
    }

    emit TimestampsOfWerkstueckReceived(t);
}

void DatabaseHandler::GetTimeStampsOfArbeitsplatz(int arbeitsplatz)
{
    QList<Timestamp*> t;

    QSqlQuery query(db);
    SendOverQuary(query, "SET @Arbeitsplatz=" + QString::number(arbeitsplatz) + ";");
    SendOverQuary(query, "SELECT * FROM vpj.rfid_timestamp WHERE Arbeitsplatz_id_Arbeitsplatz=@Arbeitsplatz;");
    QList<Prozess*> prozesslist;

    while (query.next()) {
        t.append(new Timestamp(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toUInt(), query.value(4).toInt()));
    }

    emit TimestampsOfStationReceived(t);
}


// ------------UPDATES------------ //


void DatabaseHandler::UpdateStationPlaceStatus(int ID, int status)
{
    QSqlQuery query(db);

    switch (status) {
    case 0:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=0 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    case 1:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=1 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    case 2:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=2 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    case 3:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=3 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    case 4:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=4 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    case 5:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=5 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    case 6:
        SendOverQuary(query, "UPDATE vpj.Arbeitsplatz set status=6 where id_Arbeitsplatz=" + QString::number(ID));
        break;
    }
}

void DatabaseHandler::UpdateWerkstueckFortschritt(int werkstueck, int fortschritt)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @werkstueck =" + QString::number(werkstueck) + ";");
    SendOverQuary(query, "SET @fortschritt =" + QString::number(fortschritt) + ";");
    SendOverQuary(query, "UPDATE vpj.werkstueck SET fortschritt=@fortschritt WHERE RFID_Werkstueck=@werkstueck;");
}

void DatabaseHandler::UpdateRFIDWrite(int id)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @rfid =" + QString::number(id) + ";");
    SendOverQuary(query, "UPDATE vpj.taggen SET Werkstueck_RFID_Werkstueck=@rfid WHERE id_taggen=1;");
}

void DatabaseHandler::UpdateParkplatz(int ID, int status, int roboterid)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @Parkplatz =" + QString::number(ID) + ";");
    SendOverQuary(query, "SET @Status =" + QString::number(status) + ";");
    if (roboterid == 0)
    {
        SendOverQuary(query, "SET @robo=NULL;");
    }
    else
    {
        SendOverQuary(query, "SET @robo =" + QString::number(roboterid) + ";");
    }
    SendOverQuary(query, "UPDATE vpj.parkplatz SET Status=@Status, Roboter_id_Roboter=@robo WHERE id_Parkplatz=@Parkplatz;");

}

void DatabaseHandler::SetS8P1Free(){UpdateArbeitsplatz(-1, 0, 81);}
void DatabaseHandler::SetS8P2Free(){UpdateArbeitsplatz(-1, 0, 82);}

void DatabaseHandler::UpdateArbeitsplatz(int robot, int werkstueck, int station)
{
    QSqlQuery query(db);
    if (robot == 0)
    {
        SendOverQuary(query, "SET @robot=NULL;");
    }
    else
    {
        SendOverQuary(query, "SET @robot =" + QString::number(robot) + ";");
    }

    if (werkstueck == 0)
    {
        SendOverQuary(query, "SET @werkstueck=NULL;");
    }
    else
    {
        SendOverQuary(query, "SET @werkstueck =" + QString::number(werkstueck) + ";");
    }

    SendOverQuary(query, "SET @arbeitsplatz =" + QString::number(station) + ";");

    if (werkstueck == -1)
    {
        SendOverQuary(query, "UPDATE vpj.arbeitsplatz SET roboter_id_roboter=@robot WHERE id_Arbeitsplatz=@arbeitsplatz;");
    }
    else if (robot == -1)
    {
        SendOverQuary(query, "UPDATE vpj.arbeitsplatz SET Werkstueck_RFID_Werkstueck=@werkstueck WHERE id_Arbeitsplatz=@arbeitsplatz;");
    }
    else
    {
        SendOverQuary(query, "UPDATE vpj.arbeitsplatz SET roboter_id_roboter=@robot, Werkstueck_RFID_Werkstueck=@werkstueck WHERE id_Arbeitsplatz=@arbeitsplatz;");
    }
}

void DatabaseHandler::UpdateRobotWerkstueck(int robot, int werkstueck)
{
    QSqlQuery query(db);

    SendOverQuary(query, "SET @robot =" + QString::number(robot) + ";");

    if (werkstueck == 0)
    {
        SendOverQuary(query, "SET @werkstueck=NULL;");
    }
    else
    {
        SendOverQuary(query, "SET @werkstueck =" + QString::number(werkstueck) + ";");
    }

    SendOverQuary(query, "UPDATE vpj.roboter SET Werkstueck_RFID_Werkstueck=@werkstueck WHERE id_Roboter=@robot;");

}


void DatabaseHandler::UpdateRobot1Akku(int akku){UpdateRobotAkku(1, akku);}
void DatabaseHandler::UpdateRobot2Akku(int akku){UpdateRobotAkku(2, akku);}
void DatabaseHandler::UpdateRobot3Akku(int akku){UpdateRobotAkku(3, akku);}
void DatabaseHandler::UpdateRobot4Akku(int akku){UpdateRobotAkku(4, akku);}

void DatabaseHandler::UpdateRobot1Status(int status, int pos1, int pos2){Q_UNUSED(pos1); Q_UNUSED(pos2); UpdateRobotStatus(1, status);}
void DatabaseHandler::UpdateRobot2Status(int status, int pos1, int pos2){Q_UNUSED(pos1); Q_UNUSED(pos2); UpdateRobotStatus(2, status);}
void DatabaseHandler::UpdateRobot3Status(int status, int pos1, int pos2){Q_UNUSED(pos1); Q_UNUSED(pos2); UpdateRobotStatus(3, status);}
void DatabaseHandler::UpdateRobot4Status(int status, int pos1, int pos2){Q_UNUSED(pos1); Q_UNUSED(pos2); UpdateRobotStatus(4, status);}

void DatabaseHandler::UpdateRobotAkku(int robot, int akku)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @robot =" + QString::number(robot) + ";");
    SendOverQuary(query, "SET @akku =" + QString::number(akku) + ";");
    SendOverQuary(query, "UPDATE vpj.roboter SET Akkuleistung=@akku  where id_roboter=@robot;");

}

void DatabaseHandler::UpdateRobotStatus(int robot, int status)
{
    QSqlQuery query(db);
    SendOverQuary(query, "SET @robot =" + QString::number(robot) + ";");
    SendOverQuary(query, "SET @status =" + QString::number(status) + ";");
    SendOverQuary(query, "UPDATE vpj.roboter SET Betriebsstatus=@status  where id_roboter=@robot;");
}

// ------------SETTER------------ //


void DatabaseHandler::SendProzess(Prozess *P)
{
    QSqlQuery query(db);

    int pID = P->referenzId;

    SendOverQuary(query, "SET @id_Prozess =" + QString::number(pID) + ";");
    SendOverQuary(query, "SELECT COUNT(*) FROM vpj.produktionsprozess WHERE id_Produkt=@id_Prozess;");

    if (query.next())
    {
        if (query.value(0).toInt() == 0) //Prozess dont exist _ CREATE
        {

            QString temp = "";

            for (int i = 0; i < 6; i++)
            {
                if (i >= P->Prozessschritte.length())
                {
                    temp += ", null, null";
                }
                else
                {
                    temp += ", ";
                    temp += QString::number(P->Prozessschritte.at(i)->Station());
                    temp += ", ";
                    temp += QString::number(P->Prozessschritte.at(i)->Dauer());
                }
            }
            SendOverQuary(query, "INSERT INTO vpj.Produktionsprozess VALUES (" + QString::number(pID) + temp + ")");

        }
        else //Prozess exist _ UPDATE
        {
            SendOverQuary(query, "SET @Prozess =" + QString::number(pID) + ";");

            for (int i = 0; i < 6; i++)
            {
                if (i >= P->Prozessschritte.length())
                {
                    SendOverQuary(query, "SET @station" + QString::number(i+1) + " =NULL;");// + QString::number(0) + ";");
                    SendOverQuary(query, "SET @dauer_station" + QString::number(i+1) + " =NULL;");
                }
                else
                {
                    SendOverQuary(query, "SET @station" + QString::number(i+1) + " =" + QString::number(P->Prozessschritte.at(i)->Station()) + ";");
                    SendOverQuary(query, "SET @dauer_station" + QString::number(i+1) + " =" + QString::number(P->Prozessschritte.at(i)->Dauer()) + ";");
                }

            }
            SendOverQuary(query, "UPDATE vpj.produktionsprozess SET station_1=@station1, dauer_station_1=@dauer_station1, station_2=@station2, dauer_station_2=@dauer_station2, station_3=@station3, dauer_station_3=@dauer_station3, station_4=@station4, dauer_station_4=@dauer_station4, station_5=@station5, dauer_station_5=@dauer_station5 WHERE id_Produkt= @Prozess;");
        }
    }

    //SendOverQuary(query, "select max(id_produkt)+1 from vpj.Produktionsprozess");
    //if (query.next()) {pID = query.value(0).toInt();}


}

int DatabaseHandler::GetNextLfdId()
{
    QSqlQuery query(db);
    SendOverQuary(query, "select max(RFID_werkstueck) from vpj.werkstueck");
    if (query.next()) {
        return query.value(0).toInt() + 1;
    }
    return -1;
}

void DatabaseHandler::SendAuftrag(Auftrag *A)
{
    int maxID = 0;
    QSqlQuery query(db);
    //Get highest AuftragsID
    SendOverQuary(query, "select max(id_auftrag) from vpj.auftrag");
    if (query.next()) {
        maxID = query.value(0).toInt();
        maxID++;
        //Add Auftrag to Database
        query.exec("INSERT INTO vpj.Auftrag VALUES (" + QString::number(maxID) + ", 0)");
    }

    for (int i = 0; i < A->Prozesse.length(); i++)
    {
//        int wID = 0;
//        SendOverQuary(query, "select max(RFID_werkstueck) from vpj.werkstueck");
//        if (query.next()) {
//            wID = query.value(0).toInt();
//        }

//        wID++;
//        A->Prozesse.at(i)->lfdId = wID;
        SendOverQuary(query, "INSERT INTO vpj.Werkstueck VALUES (" + QString::number(A->Prozesse.at(i)->lfdId) + ", 0," + QString::number(A->Prozesse.at(i)->referenzId) + ", " + QString::number(maxID) + ")");
    }
}

// ------------INTERNAL------------ //


void DatabaseHandler::SendOverQuary(QSqlQuery &q, const QString &name){
    q.prepare(name);
    q.exec();
}
