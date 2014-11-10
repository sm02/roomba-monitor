#include "indicateur.h"

Indicateur::Indicateur(QWidget *parent) :
    QDialog(parent)
{
}

void Indicateur::init(ControleurIndicateurs *ctrlIndic)
{
    _ctrlIndic = ctrlIndic;
}
