#include "roomba.h"

Roomba::Roomba(QObject *parent) :
    QObject(parent)
{
    _mesurage=new Mesurage;
    _liaison=new Liaison;

    _mesurage->setLiaison(_liaison);

    connect(_mesurage,SIGNAL(nouvelleMesure()),this,SIGNAL(nouvelleMesure()));
}

Roomba::~Roomba()
{
    if (_liaison->connexionEtablie()) _liaison->deconnecter();
    delete(_mesurage);
    delete(_liaison);
}

bool Roomba::debuterEnregistrement() {
    return _mesurage->demarrerAcquisition();
}

void Roomba::finirEnregistrement() {
    _mesurage->arreterAcquisition();
}

void Roomba::configurerLiaison(ConfigLiaison &cfg)
{
    _liaison->configurer(cfg);
}

qint32 Roomba::mesure(eCapt capt, qint32 rang) const
{
    return _mesurage->mesure(capt,rang);
}

quint32 Roomba::nbTramesIncompletes() const
{
    return _mesurage->nbTramesIncompletes();
}

quint32 Roomba::nbTrames() const
{
    return _mesurage->nbMesures();
}

bool Roomba::connecter()
{
    return _liaison->connecter();
}

bool Roomba::deconnecter()
{
    return _liaison->deconnecter();
}

void Roomba::sauvegarder(QString nomFichier)
{
    _mesurage->sauvegarder(nomFichier);
}

bool Roomba::charger(QString nomFichier)
{
    return _mesurage->charger(nomFichier);
}
