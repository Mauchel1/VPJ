//#ifndef INITDB_H
//#define INITDB_H

//#include <QtSql>
//#include <QSqlDatabase>
//#include <QSqlQuery>


//QSqlDatabase InitDb()
//{

//    //https://www.seppemagiels.com/blog/create-mysql-driver-qt5-windows
//    //qDebug() << QSqlDatabase::drivers();
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("192.168.0.107");
//    db.setPort(3306);
//    db.setDatabaseName("vpj");
//    db.setUserName("root");
//    db.setPassword("1234");

//    //    C:\Program Files\MySQL\MySQL Connector.C 6.1\lib
//    bool ok = db.open();

//    Q_ASSERT(ok);
//    Q_UNUSED(ok);

//    QSqlError err;
//    if (err.type() != QSqlError::NoError){
//        qCritical() << err.text();
//    }

//    return db;
//}


//void SendOverQuary(QSqlQuery &q, const QString &name){
//    q.prepare(name);
//    q.exec();
//}

//void SendOverNewQuary(const QString &name){
//    QSqlQuery q;
//    q.prepare(name);
//    q.exec();
//}

//void AddBindToQuary(){

//}





//#endif // INITDB_H
