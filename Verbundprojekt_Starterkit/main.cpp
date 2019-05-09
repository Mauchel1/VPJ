#include "mainwindow.h"
#include "databasehandler.h"
#include "udphandler.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    UDPHandler robotUDP(QHostAddress("192.168.0.14"), 25040, 25014); //MUSS IM STARTERKIT ANGEPASST WERDEN
    UDPHandler navigationUDP(25000);

    DatabaseHandler dbhandler;

    QObject::connect(&robotUDP, &UDPHandler::DataReceived, &w, &MainWindow::updateRobotData);
    QObject::connect(&w, &MainWindow::writeValues, &robotUDP, &UDPHandler::WriteData);
    QObject::connect(&w, &MainWindow::updateDBValues, &dbhandler, &DatabaseHandler::UpdateValues);
    QObject::connect(&w, &MainWindow::getDBValues, &dbhandler, &DatabaseHandler::GetValues);
    QObject::connect(&dbhandler, &DatabaseHandler::ValuesReceived, &w, &MainWindow::updateTableValues);

    return a.exec();
}
