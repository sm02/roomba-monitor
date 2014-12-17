#include "controleurindicateurs.h"
#include "mesurage.h"

#include "indicateurstatus.h"
#include "indicateurdebug.h"
#include "indicateurmoteurscourants.h"

ControleurIndicateurs::ControleurIndicateurs(QObject *parent, Roomba *r) :
    QObject(parent),
    _rmb(r),
    _numMesureActive(0)
{
}

ControleurIndicateurs::~ControleurIndicateurs()
{
    for (int i=0;i<NB_INDIC;i++) delete indic[i];
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
    indic[0] = new indicateurMoteursCourants;
    indic[1] = new IndicateurDebug;

    for (int i=0;i<NB_INDIC;i++) {
        indic[i]->init(this);
        /* Paramétrage de la fenêtre (Qt::CustomizeWindowHint)
         * Qt::MSWindowsFixedSizeDialogHint   : Taille fixe
         * Qt::WindowMinimizeButtonHint       : Possible de réduire
         */
        indic[i]->setWindowFlags(Qt::CustomizeWindowHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint );
        indic[i]->show();
    }
}

qint32 ControleurIndicateurs::mesureActive(eCapt capt) const
{
    return _rmb->mesure(capt,_numMesureActive);
}

void ControleurIndicateurs::majIndicateurs()
{
    for (int i=0;i<NB_INDIC;i++) {
        indic[i]->mettreAJourValeur();
    }
}

void ControleurIndicateurs::selectionnerMesure(qint32 numMesure)
{
    setNumMesureActive(numMesure);
}

void ControleurIndicateurs::close()
{
    for (int i=0;i<NB_INDIC;i++) {
        indic[i]->close();
    }
}

