#include "databasehandler.h"
#include <QString>

DatabaseHandler::DatabaseHandler(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.0.107");
    db.setPort(3306);
    db.setDatabaseName("starterkit");
    db.setUserName("root");
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

void DatabaseHandler::GetValues()
{
    QSqlQuery query(db);
    query.prepare("SELECT Name FROM starterkit.sql_vpj");
    query.exec();

    QList<QString> values;

    while (query.next()) {
        if (query.size() > 0)
        {
            values.append(query.value(0).toString());
        }
    }
    emit ValuesReceived(values);
}

void DatabaseHandler::UpdateValues(QVector<QString> values)
{
    QSqlQuery query(db);
    query.exec("UPDATE starterkit.sql_vpj SET Name = '" + values[0] + "' WHERE Nummer = 1");
    query.exec("UPDATE starterkit.sql_vpj SET Name = '" + values[1] + "' WHERE Nummer = 2");
}
