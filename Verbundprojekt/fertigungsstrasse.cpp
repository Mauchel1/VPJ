#include "fertigungsstrasse.h"

Fertigungsstrasse::Fertigungsstrasse() : S1(10), S2(20), S3(30), S4(40), S5(50), S6(60), S7(70), S8(80), P1(1), P2(2), P3(3), P4(4), L1(5), L2(6)
{

}


Platz *Fertigungsstrasse::GetStationPlatzByID(int id)
{
    if (S1.P1.ID() == id){ return &S1.P1;}
    else if (S1.P2.ID() == id){ return &S1.P2;}
    else if (S2.P1.ID() == id){ return &S2.P1;}
    else if (S2.P2.ID() == id){ return &S2.P2;}
    else if (S3.P1.ID() == id){ return &S3.P1;}
    else if (S3.P2.ID() == id){ return &S3.P2;}
    else if (S4.P1.ID() == id){ return &S4.P1;}
    else if (S4.P2.ID() == id){ return &S4.P2;}
    else if (S5.P1.ID() == id){ return &S5.P1;}
    else if (S5.P2.ID() == id){ return &S5.P2;}
    else if (S6.P1.ID() == id){ return &S6.P1;}
    else if (S6.P2.ID() == id){ return &S6.P2;}
    else if (S7.P1.ID() == id){ return &S7.P1;}
    else if (S7.P2.ID() == id){ return &S7.P2;}
    else if (S8.P1.ID() == id){ return &S8.P1;}
    else if (S8.P2.ID() == id){ return &S8.P2;}
    else { return nullptr;}
}

Parkplatz *Fertigungsstrasse::GetPlatzByID(int id)
{
    if (P1.ID() == id){ return &P1;}
    if (P2.ID() == id){ return &P2;}
    if (P3.ID() == id){ return &P3;}
    if (P4.ID() == id){ return &P4;}
    if (L1.ID() == id){ return &L1;}
    if (L2.ID() == id){ return &L2;}
    else { return nullptr;}
}
