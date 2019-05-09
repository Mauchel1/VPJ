#include "auftragsitem.h"
#include "ui_auftragsitem.h"

Auftragsitem::Auftragsitem(Auftrag* a, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Auftragsitem)
{
    ui->setupUi(this);
    auftrag = a;
    QObject::connect(auftrag, &Auftrag::FortschrittUpdated, this, &Auftragsitem::UpdateAuftragsFortschritt);
}

Auftragsitem::~Auftragsitem()
{
    delete ui;
}

void Auftragsitem::SetLabelText(QString s)
{
   ui->label->setText(s);
}

void Auftragsitem::UpdateAuftragsFortschritt()
{
    ui->progressBar->setValue(auftrag->fortschritt);
    if (auftrag->fortschritt == 100)
    {
        ui->progressBar->setStyleSheet("QProgressBar::chunk {background-color: green}");
    }
}
