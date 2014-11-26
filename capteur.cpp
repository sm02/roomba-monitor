#include "capteur.h"

Capteur::Capteur()
{
    _valeurs=new dqint;
}

Capteur::~Capteur()
{
    delete(_valeurs);
}


qint32 Capteur::valeur(const qint32 rang) const
{
    if (rang<0) {
        return _valeurs->back();
    } else {
        return _valeurs->at(rang);
    }
}



void Capteur::ajouterValeur(const qint32 value)
{
    _valeurs->push_back(value);
}




quint32 Capteur::size()
{
    return _valeurs->size();
}
