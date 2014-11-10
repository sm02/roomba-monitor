#include "controleurindicateurs.h"
#include "mesurage.h"
#include "indicateurstatus.h"
#include "indicateurdebug.h"

ControleurIndicateurs::ControleurIndicateurs(QObject *parent, Roomba *r) :
    QObject(parent),
    _rmb(r),
    _numMesureActive(0)
{
}

ControleurIndicateurs::~ControleurIndicateurs()
{
    delete indic1;
    delete indic2;
}

qint32 ControleurIndicateurs::numMesureActive() const
{
    return _numMesureActive;
}

void ControleurIndicateurs::setNumMesureActive(const qint32 &numMesureActive)
{
    _numMesureActive = numMesureActive;
    majIndicateurs();
}

void ControleurIndicateurs::ouvrirIndicateurs()
{
    indic1 = new IndicateurStatus;
    indic1->init(this);
    indic1->show();

    indic2 = new IndicateurDebug;
    indic2->init(this);
    indic2->show();
}

qint32 ControleurIndicateurs::mesureActive(eCapt capt) const
{
    return _rmb->mesure(capt,_numMesureActive);
}

void ControleurIndicateurs::majIndicateurs()
{
    indic1->mettreAJourValeur();
    indic2->mettreAJourValeur();
}

void ControleurIndicateurs::selectionnerMesure(qint32 numMesure)
{
    setNumMesureActive(numMesure);
}

void ControleurIndicateurs::close()
{
    indic1->close();
    indic2->close();
}

