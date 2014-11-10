/*! \file roomba.h
* \brief Class Roomba
* \author    SM
* \version   0.1
* \date      nov. 2014
* \copyright GNU GPL v3
*/
#ifndef ROOMBA_H
#define ROOMBA_H

#include <QObject>
#include "mesurage.h"
#include "liaison.h"

class Roomba : public QObject
{
    Q_OBJECT
public:
    explicit Roomba(QObject *parent = 0);
    ~Roomba();

public slots:
    bool debuterEnregistrement();
    void finirEnregistrement();
    void configurerLiaison(ConfigLiaison& cfg);
    qint32 mesure(eCapt capt,qint32 rang=-1) const;
    quint32 nbTramesIncompletes() const;
    quint32 nbMesures() const;
    bool connecter();
    bool deconnecter();
    bool estConnecte();
    void sauvegarder(QString nomFichier);
    bool charger(QString nomFichier);

signals:
    void nouvelleMesure();

private:
    Mesurage *_mesurage;
    Liaison *_liaison;
    ConfigLiaison *_cfg;
};

#endif // ROOMBA_H
