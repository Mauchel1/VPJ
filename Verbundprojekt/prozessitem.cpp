#include "prozessitem.h"
#include "ui_prozessitem.h"

Prozessitem::Prozessitem(Prozess* p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prozessitem)
{
    ui->setupUi(this);
    prozess = p;
    QObject::connect(prozess, &Prozess::FortschrittUpdated, this, &Prozessitem::UpdateProzessFortschritt);
}

Prozessitem::~Prozessitem()
{
    delete ui;
}

void Prozessitem::SetLabelText(QString s)
{
   ui->label->setText(s);
}

void Prozessitem::UpdateProzessFortschritt()
{
    ui->progressBar->setValue(prozess->Fortschritt());
    if (prozess->Fortschritt() == 100)
    {
        ui->progressBar->setStyleSheet("QProgressBar::chunk {background-color: green}");
    }
}

void Prozessitem::UpdateProzessBlocked()
{
    ui->progressBar->setStyleSheet("QProgressBar {background-color: red}");
}
