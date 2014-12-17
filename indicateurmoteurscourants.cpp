#include "indicateurmoteurscourants.h"
#include "ui_indicateurmoteurscourants.h"
#include "analogwidgets/manometer.h"

indicateurMoteursCourants::indicateurMoteursCourants(QWidget *parent) :
    Indicateur(parent),
    ui(new Ui::indicateurMoteursCourants)
{
    ui->setupUi(this);
    manoCourantMoteurG = new ManoMeter(ui->widget);
    manoCourantMoteurD = new ManoMeter(ui->widget);
    manoCourantMoteurBrossePrinc = new ManoMeter(ui->widget);
    manoCourantMoteurBrosseLateral = new ManoMeter(ui->widget);
}

indicateurMoteursCourants::~indicateurMoteursCourants()
{
    delete ui;
}

void indicateurMoteursCourants::init(ControleurIndicateurs *ctrlIndic)
{
    _ctrlIndic = ctrlIndic;
}

void indicateurMoteursCourants::mettreAJourValeur()
{
    manoCourantMoteurG->setGeometry(QRect(40, 10, 90, 90));
    manoCourantMoteurD->setGeometry(QRect(40, 100, 90, 90));
    manoCourantMoteurBrossePrinc->setGeometry(QRect(180, 10, 90, 90));
    manoCourantMoteurBrosseLateral->setGeometry(QRect(180, 100, 90, 90));


    manoCourantMoteurG->setValue(_ctrlIndic->mesureActive(courantMoteurG));
    manoCourantMoteurG->setMaximum(10000);
    manoCourantMoteurG->setMinimum(-10000);
    manoCourantMoteurG->setNominal(0);
    manoCourantMoteurG->setCritical(10000);
    manoCourantMoteurG->setSuffix(QString(" mA"));
    manoCourantMoteurG->setValueOffset(90);

    manoCourantMoteurD->setValue(_ctrlIndic->mesureActive(courantMoteurD));
    manoCourantMoteurD->setMaximum(10000);
    manoCourantMoteurD->setMinimum(-10000);
    manoCourantMoteurD->setNominal(0);
    manoCourantMoteurD->setCritical(10000);
    manoCourantMoteurD->setSuffix(QString(" mA"));
    manoCourantMoteurD->setValueOffset(90);

    manoCourantMoteurBrossePrinc->setValue(_ctrlIndic->mesureActive(courantMoteurBrossePrinc));
    manoCourantMoteurBrossePrinc->setMaximum(10000);
    manoCourantMoteurBrossePrinc->setMinimum(-10000);
    manoCourantMoteurBrossePrinc->setNominal(0);
    manoCourantMoteurBrossePrinc->setCritical(10000);
    manoCourantMoteurBrossePrinc->setSuffix(QString(" mA"));
    manoCourantMoteurBrossePrinc->setValueOffset(90);

    manoCourantMoteurBrosseLateral->setValue(_ctrlIndic->mesureActive(courantMoteurBrosseLateral));
    manoCourantMoteurBrosseLateral->setMaximum(10000);
    manoCourantMoteurBrosseLateral->setMinimum(-10000);
    manoCourantMoteurBrosseLateral->setNominal(0);
    manoCourantMoteurBrosseLateral->setCritical(10000);
    manoCourantMoteurBrosseLateral->setSuffix(QString(" mA"));
    manoCourantMoteurBrosseLateral->setValueOffset(90);

}
