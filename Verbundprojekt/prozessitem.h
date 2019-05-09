#ifndef PROZESSITEM_H
#define PROZESSITEM_H

#include <QWidget>
#include "prozess.h"

namespace Ui {
class Prozessitem;
}

class Prozessitem : public QWidget
{
    Q_OBJECT

public:
    explicit Prozessitem(Prozess* p, QWidget *parent = nullptr);
    ~Prozessitem();
    Prozess *prozess;

private:
    Ui::Prozessitem *ui;

public slots:
    void SetLabelText(QString s);
    void UpdateProzessFortschritt();
    void UpdateProzessBlocked();
};

#endif // PROZESSITEM_H
