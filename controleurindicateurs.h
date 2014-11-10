/*!
* \file      controleurindicateurs.h
* \brief     Affichage des indicateurs (ouverture et fermeture de fenêtre, mise à jour des valeurs)
* \details
* \author    SM
* \version   0.1
* \date      nov. 2014
* \copyright GNU GPL v3
*/

#ifndef CONTROLEURINDICATEURS_H
#define CONTROLEURINDICATEURS_H

#include <QObject>
#include "roomba.h"

#define NB_INDIC 2  ///!< Le nombre d'indicateurs à gérer

class Indicateur; //déclaration avancée

//! \brief Affichage des indicateurs (ouverture et fermeture de fenêtre, mise à jour des valeurs)
class ControleurIndicateurs : public QObject
{
    Q_OBJECT
public:
    explicit ControleurIndicateurs(QObject *parent = 0,Roomba *r = 0);
    ~ControleurIndicateurs();

    qint32 numMesureActive() const;
    void setNumMesureActive(const qint32 &numMesureActive);
    void ouvrirIndicateurs();

    qint32 mesureActive(eCapt capt) const;
private:
    Roomba *_rmb;
    qint32 _numMesureActive;
    Indicateur *(indic[NB_INDIC]);

signals:

public slots:
    void majIndicateurs();
    void selectionnerMesure(qint32 numMesure);
    void close();
};

#endif // CONTROLEURINDICATEURS_H
