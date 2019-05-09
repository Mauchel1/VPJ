#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class DatabaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseHandler(QObject *parent = nullptr);
    QSqlDatabase db;

    void GetValues();

signals:
    void ValuesReceived(QList<QString> values);

public slots:

    void UpdateValues(QVector<QString> values);

};

#endif // DATABASEHANDLER_H
