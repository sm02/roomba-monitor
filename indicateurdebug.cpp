#include "indicateurdebug.h"
#include "ui_indicateurdebug.h"

IndicateurDebug::IndicateurDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndicateurDebug)
{
    ui->setupUi(this);
}

IndicateurDebug::~IndicateurDebug()
{
    delete ui;
}

void IndicateurDebug::init(ControleurIndicateurs *ctrlIndic)
{
    _ctrlIndic = ctrlIndic;
}

void IndicateurDebug::mettreAJourValeur()
{
    QString text="";
    text+=QString("soulevRoueG:%1\n").arg(_ctrlIndic->mesureActive(soulevRoueG));
    text+=QString("soulevRoueD:%1\n").arg(_ctrlIndic->mesureActive(soulevRoueD));
    text+=QString("chocG:%1\n").arg(_ctrlIndic->mesureActive(chocG));
    text+=QString("chocD:%1\n").arg(_ctrlIndic->mesureActive(chocD));
    text+=QString("mur:%1\n").arg(_ctrlIndic->mesureActive(mur));
    text+=QString("videG:%1   ").arg(_ctrlIndic->mesureActive(videG));
    text+=QString("videAvG:%1   ").arg(_ctrlIndic->mesureActive(videAvG));
    text+=QString("videAvD:%1   ").arg(_ctrlIndic->mesureActive(videAvD));
    text+=QString("videD:%1\n").arg(_ctrlIndic->mesureActive(videD));
    text+=QString("murVirtuel:%1\n").arg(_ctrlIndic->mesureActive(murVirtuel));
    text+=QString("surIntensRoueG:%1   ").arg(_ctrlIndic->mesureActive(surIntensRoueG));
    text+=QString("surIntensRoueD:%1  ").arg(_ctrlIndic->mesureActive(surIntensRoueD));
    text+=QString("surIntensBrossePrinc:%1   ").arg(_ctrlIndic->mesureActive(surIntensBrossePrinc));
    text+=QString("surIntensBrosseLat:%1\n").arg(_ctrlIndic->mesureActive(surIntensBrosseLat));
    text+=QString("nivPoussiere:%1\n").arg(_ctrlIndic->mesureActive(nivPoussiere));
    text+=QString("infrarougeOmnidir:%1   ").arg(_ctrlIndic->mesureActive(infrarougeOmnidir));
    text+=QString("infrarougeG:%1   ").arg(_ctrlIndic->mesureActive(infrarougeG));
    text+=QString("infrarougeD:%1\n").arg(_ctrlIndic->mesureActive(infrarougeD));
    text+=QString("boutons Horloge:%1   ").arg(_ctrlIndic->mesureActive(boutonHorloge));
    text+=QString("Prog:%1   ").arg(_ctrlIndic->mesureActive(boutonProg));
    text+=QString("Jour:%1   ").arg(_ctrlIndic->mesureActive(boutonJour));
    text+=QString("Heure:%1   ").arg(_ctrlIndic->mesureActive(boutonHeure));
    text+=QString("Min:%1   ").arg(_ctrlIndic->mesureActive(boutonMin));
    text+=QString("Base:%1   ").arg(_ctrlIndic->mesureActive(boutonBase));
    text+=QString("Spot:%1  ").arg(_ctrlIndic->mesureActive(boutonSpot));
    text+=QString("Nett:%1\n").arg(_ctrlIndic->mesureActive(boutonNett));
    text+=QString("distance:%1   ").arg(_ctrlIndic->mesureActive(distance));
    text+=QString("angle:%1\n").arg(_ctrlIndic->mesureActive(angle));
    text+=QString("etatCharge:%1\n").arg(_ctrlIndic->mesureActive(etatCharge));
    text+=QString("voltage:%1   ").arg(_ctrlIndic->mesureActive(voltage));
    text+=QString("courant:%1\n").arg(_ctrlIndic->mesureActive(courant));
    text+=QString("temperature:%1\n").arg(_ctrlIndic->mesureActive(temperature));
    text+=QString("chargeBat:%1   ").arg(_ctrlIndic->mesureActive(chargeBat));
    text+=QString("capaciteBat:%1\n").arg(_ctrlIndic->mesureActive(capaciteBat));
    text+=QString("signalMur:%1   ").arg(_ctrlIndic->mesureActive(signalMur));
    text+=QString("signalVideG:%1   ").arg(_ctrlIndic->mesureActive(signalVideG));
    text+=QString("signalVideAvG:%1   ").arg(_ctrlIndic->mesureActive(signalVideAvG));
    text+=QString("signalVideAvD:%1   ").arg(_ctrlIndic->mesureActive(signalVideAvD));
    text+=QString("signalVideD:%1\n").arg(_ctrlIndic->mesureActive(signalVideD));
    text+=QString("chargeurBase:%1   ").arg(_ctrlIndic->mesureActive(chargeurBase));
    text+=QString("chargeurInterne:%1\n").arg(_ctrlIndic->mesureActive(chargeurInterne));
    text+=QString("mode:%1\n").arg(_ctrlIndic->mesureActive(mode));
    text+=QString("noMusique:%1   ").arg(_ctrlIndic->mesureActive(noMusique));
    text+=QString("musique:%1\n").arg(_ctrlIndic->mesureActive(musique));
    text+=QString("nombrePaquets:%1\n").arg(_ctrlIndic->mesureActive(nombrePaquets));
    text+=QString("vitesseReq:%1   ").arg(_ctrlIndic->mesureActive(vitesseReq));
    text+=QString("rayonReq:%1\n").arg(_ctrlIndic->mesureActive(rayonReq));
    text+=QString("vitesseDReq:%1   ").arg(_ctrlIndic->mesureActive(vitesseDReq));
    text+=QString("vitesseGReq:%1\n").arg(_ctrlIndic->mesureActive(vitesseGReq));
    text+=QString("encodeurD:%1   ").arg(_ctrlIndic->mesureActive(encodeurD));
    text+=QString("encodeurG:%1\n").arg(_ctrlIndic->mesureActive(encodeurG));
    text+=QString("oeilLateralD:%1   ").arg(_ctrlIndic->mesureActive(oeilLateralD));
    text+=QString("oeilAvantD:%1   ").arg(_ctrlIndic->mesureActive(oeilAvantD));
    text+=QString("oeilCentreD:%1   ").arg(_ctrlIndic->mesureActive(oeilCentreD));
    text+=QString("oeilCentreG:%1   ").arg(_ctrlIndic->mesureActive(oeilCentreG));
    text+=QString("oeilAvantG:%1   ").arg(_ctrlIndic->mesureActive(oeilAvantG));
    text+=QString("oeilLateralG:%1\n").arg(_ctrlIndic->mesureActive(oeilLateralG));
    text+=QString("signal OeilLateralG:%1   ").arg(_ctrlIndic->mesureActive(signalOeilLateralG));
    text+=QString("OeilAvantG:%1   ").arg(_ctrlIndic->mesureActive(signalOeilAvantG));
    text+=QString("OeilCentreG:%1  ").arg(_ctrlIndic->mesureActive(signalOeilCentreG));
    text+=QString("OeilCentreD:%1  ").arg(_ctrlIndic->mesureActive(signalOeilCentreD));
    text+=QString("OeilAvantD:%1   ").arg(_ctrlIndic->mesureActive(signalOeilAvantD));
    text+=QString("OeilLateralD:%1\n").arg(_ctrlIndic->mesureActive(signalOeilLateralD));
    text+=QString("courant MoteurG:%1   ").arg(_ctrlIndic->mesureActive(courantMoteurG));
    text+=QString("MoteurD:%1\n").arg(_ctrlIndic->mesureActive(courantMoteurD));
    text+=QString("CourantMoteurBrossePrinc:%1   ").arg(_ctrlIndic->mesureActive(courantMoteurBrossePrinc));
    text+=QString("MoteurBrosseLateral:%1\n").arg(_ctrlIndic->mesureActive(courantMoteurBrosseLateral));
    text+=QString("roueFolle:%1").arg(_ctrlIndic->mesureActive(roueFolle));
    ui->text->setText(text);
}
