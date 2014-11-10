#include "indicateurstatus.h"
#include "ui_indicateurstatus.h"

#include "mesurage.h"
#include "controleurindicateurs.h"

IndicateurStatus::IndicateurStatus(QWidget *parent) :
    Indicateur(parent),
    ui(new Ui::IndicateurStatus)
{
    ui->setupUi(this);
}

IndicateurStatus::~IndicateurStatus()
{
    delete ui;
}

void IndicateurStatus::init(ControleurIndicateurs *ctrlIndic)
{
    _ctrlIndic = ctrlIndic;
}

void IndicateurStatus::mettreAJourValeur()
{
    ui->label->setText(QString("%1").arg(_ctrlIndic->mesureActive(signalVideAvG)));
}
