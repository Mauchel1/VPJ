#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer();
    timer->setSingleShot(false);
    timer->setInterval(1000);
    timer->start();
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::prepareValues);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::prepareValues()
{
    counter++;
    ui->lineEdit_4->setText(QString::number(counter));

    QVector<int> values(5);
    values[0] = ui->checkBox->isChecked();
    values[1] = (ui->lineEdit->text().toInt());
    values[2] = (ui->lineEdit_2->text().toInt());
    values[3] = (ui->lineEdit_3->text().toInt());
    values[4] = (ui->lineEdit_4->text().toInt());
    emit writeValues(values);
}

void MainWindow::updateTableValues(QList<QString> values)
{
    ui->label_13->setText(values[0]);
    ui->label_15->setText(values[1]);
}

void MainWindow::updateRobotData(QVector<int> values)
{
    ui->lineEdit_6->setText(QString::number(values[0]));
    ui->lineEdit_5->setText(QString::number(values[1]));
}

void MainWindow::on_lineEdit_editingFinished()
{
    prepareValues();
}

void MainWindow::on_lineEdit_2_editingFinished()
{
    prepareValues();
}

void MainWindow::on_lineEdit_3_editingFinished()
{
    prepareValues();
}

void MainWindow::on_lineEdit_4_editingFinished()
{
    prepareValues();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    Q_UNUSED(checked);
    prepareValues();
}

void MainWindow::on_read_clicked()
{
    emit getDBValues();
}

void MainWindow::on_writeR_clicked()
{
    QVector<QString> values(2);
    values[0] = "Robotino";
    values[1] = ui->label_15->text();
    emit updateDBValues(values);
}

void MainWindow::on_writeM_clicked()
{
    QVector<QString> values(2);
    values[0] = "MATLAB";
    values[1] = ui->label_15->text();
    emit updateDBValues(values);
}

void MainWindow::on_writeP_clicked()
{
    QVector<QString> values(2);
    values[0] = ui->label_13->text();
    values[1] = "PC";
    emit updateDBValues(values);
}

void MainWindow::on_writeC_clicked()
{
    QVector<QString> values(2);
    values[0] = ui->label_13->text();
    values[1] = "CoDeSys";
    emit updateDBValues(values);
}
