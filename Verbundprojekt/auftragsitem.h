#ifndef AUFTRAGSITEM_H
#define AUFTRAGSITEM_H

#include <QWidget>
#include "auftrag.h"

namespace Ui {
class Auftragsitem;
}

class Auftragsitem : public QWidget
{
    Q_OBJECT

public:
    explicit Auftragsitem(Auftrag* a, QWidget *parent = nullptr);
    ~Auftragsitem();
    Auftrag* auftrag;

private:
    Ui::Auftragsitem *ui;

public slots:
    void SetLabelText(QString s);
    void UpdateAuftragsFortschritt();
};

#endif // AUFTRAGSITEM_H
